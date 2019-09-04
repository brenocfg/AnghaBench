#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
typedef  struct scatterlist u8 ;
struct tls_sw_context_rx {int /*<<< orphan*/  control; int /*<<< orphan*/  aead_recv; } ;
struct TYPE_2__ {int overhead_size; int prepend_size; int /*<<< orphan*/  rec_seq_size; int /*<<< orphan*/  rec_seq; struct scatterlist* iv; int /*<<< orphan*/  iv_size; } ;
struct tls_context {TYPE_1__ rx; } ;
struct strp_msg {int full_len; int offset; } ;
struct sock {int /*<<< orphan*/  sk_allocation; } ;
struct sk_buff {int dummy; } ;
struct iov_iter {int dummy; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int EBADMSG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INT_MAX ; 
 int TLS_AAD_SPACE_SIZE ; 
 int TLS_CIPHER_AES_GCM_128_SALT_SIZE ; 
 int TLS_HEADER_SIZE ; 
 int crypto_aead_ivsize (int /*<<< orphan*/ ) ; 
 int crypto_aead_reqsize (int /*<<< orphan*/ ) ; 
 int iov_iter_npages (struct iov_iter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct scatterlist*) ; 
 struct scatterlist* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct scatterlist*,struct scatterlist*,int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int sg_nents (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,struct scatterlist*,int) ; 
 int skb_copy_bits (struct sk_buff*,int,struct scatterlist*,int /*<<< orphan*/ ) ; 
 int skb_cow_data (struct sk_buff*,int /*<<< orphan*/ ,struct sk_buff**) ; 
 int skb_to_sgvec (struct sk_buff*,struct scatterlist*,int,int) ; 
 struct strp_msg* strp_msg (struct sk_buff*) ; 
 int tls_do_decryption (struct sock*,struct scatterlist*,struct scatterlist*,struct scatterlist*,int const,struct aead_request*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 int /*<<< orphan*/  tls_make_aad (struct scatterlist*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tls_sw_context_rx* tls_sw_ctx_rx (struct tls_context*) ; 
 int zerocopy_from_iter (struct sock*,struct iov_iter*,int const,int*,int*,struct scatterlist*,int,int) ; 

__attribute__((used)) static int decrypt_internal(struct sock *sk, struct sk_buff *skb,
			    struct iov_iter *out_iov,
			    struct scatterlist *out_sg,
			    int *chunk, bool *zc)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);
	struct strp_msg *rxm = strp_msg(skb);
	int n_sgin, n_sgout, nsg, mem_size, aead_size, err, pages = 0;
	struct aead_request *aead_req;
	struct sk_buff *unused;
	u8 *aad, *iv, *mem = NULL;
	struct scatterlist *sgin = NULL;
	struct scatterlist *sgout = NULL;
	const int data_len = rxm->full_len - tls_ctx->rx.overhead_size;

	if (*zc && (out_iov || out_sg)) {
		if (out_iov)
			n_sgout = iov_iter_npages(out_iov, INT_MAX) + 1;
		else
			n_sgout = sg_nents(out_sg);
	} else {
		n_sgout = 0;
		*zc = false;
	}

	n_sgin = skb_cow_data(skb, 0, &unused);
	if (n_sgin < 1)
		return -EBADMSG;

	/* Increment to accommodate AAD */
	n_sgin = n_sgin + 1;

	nsg = n_sgin + n_sgout;

	aead_size = sizeof(*aead_req) + crypto_aead_reqsize(ctx->aead_recv);
	mem_size = aead_size + (nsg * sizeof(struct scatterlist));
	mem_size = mem_size + TLS_AAD_SPACE_SIZE;
	mem_size = mem_size + crypto_aead_ivsize(ctx->aead_recv);

	/* Allocate a single block of memory which contains
	 * aead_req || sgin[] || sgout[] || aad || iv.
	 * This order achieves correct alignment for aead_req, sgin, sgout.
	 */
	mem = kmalloc(mem_size, sk->sk_allocation);
	if (!mem)
		return -ENOMEM;

	/* Segment the allocated memory */
	aead_req = (struct aead_request *)mem;
	sgin = (struct scatterlist *)(mem + aead_size);
	sgout = sgin + n_sgin;
	aad = (u8 *)(sgout + n_sgout);
	iv = aad + TLS_AAD_SPACE_SIZE;

	/* Prepare IV */
	err = skb_copy_bits(skb, rxm->offset + TLS_HEADER_SIZE,
			    iv + TLS_CIPHER_AES_GCM_128_SALT_SIZE,
			    tls_ctx->rx.iv_size);
	if (err < 0) {
		kfree(mem);
		return err;
	}
	memcpy(iv, tls_ctx->rx.iv, TLS_CIPHER_AES_GCM_128_SALT_SIZE);

	/* Prepare AAD */
	tls_make_aad(aad, rxm->full_len - tls_ctx->rx.overhead_size,
		     tls_ctx->rx.rec_seq, tls_ctx->rx.rec_seq_size,
		     ctx->control);

	/* Prepare sgin */
	sg_init_table(sgin, n_sgin);
	sg_set_buf(&sgin[0], aad, TLS_AAD_SPACE_SIZE);
	err = skb_to_sgvec(skb, &sgin[1],
			   rxm->offset + tls_ctx->rx.prepend_size,
			   rxm->full_len - tls_ctx->rx.prepend_size);
	if (err < 0) {
		kfree(mem);
		return err;
	}

	if (n_sgout) {
		if (out_iov) {
			sg_init_table(sgout, n_sgout);
			sg_set_buf(&sgout[0], aad, TLS_AAD_SPACE_SIZE);

			*chunk = 0;
			err = zerocopy_from_iter(sk, out_iov, data_len, &pages,
						 chunk, &sgout[1],
						 (n_sgout - 1), false);
			if (err < 0)
				goto fallback_to_reg_recv;
		} else if (out_sg) {
			memcpy(sgout, out_sg, n_sgout * sizeof(*sgout));
		} else {
			goto fallback_to_reg_recv;
		}
	} else {
fallback_to_reg_recv:
		sgout = sgin;
		pages = 0;
		*chunk = 0;
		*zc = false;
	}

	/* Prepare and submit AEAD request */
	err = tls_do_decryption(sk, sgin, sgout, iv, data_len, aead_req);

	/* Release the pages in case iov was mapped to pages */
	for (; pages > 0; pages--)
		put_page(sg_page(&sgout[pages]));

	kfree(mem);
	return err;
}