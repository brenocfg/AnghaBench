#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tls_sw_context_tx {size_t sg_plaintext_size; scalar_t__ sg_plaintext_num_elem; struct scatterlist* sg_plaintext_data; } ;
struct TYPE_3__ {size_t overhead_size; } ;
struct tls_context {struct scatterlist* pending_open_record_frags; TYPE_1__ tx; } ;
struct sock {int sk_err; TYPE_2__* sk_socket; } ;
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (struct scatterlist*) ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int ENOTSUPP ; 
 int MSG_DONTWAIT ; 
 int MSG_MORE ; 
 int MSG_NOSIGNAL ; 
 int MSG_SENDPAGE_NOTLAST ; 
 int /*<<< orphan*/  SOCKWQ_ASYNC_NOSPACE ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int TLS_MAX_PAYLOAD_SIZE ; 
 unsigned char TLS_RECORD_TYPE_DATA ; 
 int alloc_encrypted_sg (struct sock*,size_t) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,size_t,int) ; 
 int /*<<< orphan*/  sg_unmark_end (struct scatterlist*) ; 
 int /*<<< orphan*/  sk_clear_bit (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  sk_mem_charge (struct sock*,size_t) ; 
 int sk_stream_error (struct sock*,int,int) ; 
 int /*<<< orphan*/  sk_stream_memory_free (struct sock*) ; 
 int sk_stream_wait_memory (struct sock*,long*) ; 
 long sock_sndtimeo (struct sock*,int) ; 
 scalar_t__ tls_complete_pending_work (struct sock*,struct tls_context*,int,long*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 scalar_t__ tls_is_pending_closed_record (struct tls_context*) ; 
 int tls_push_record (struct sock*,int,unsigned char) ; 
 struct tls_sw_context_tx* tls_sw_ctx_tx (struct tls_context*) ; 
 int /*<<< orphan*/  trim_both_sgl (struct sock*,size_t) ; 

int tls_sw_sendpage(struct sock *sk, struct page *page,
		    int offset, size_t size, int flags)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	int ret = 0;
	long timeo = sock_sndtimeo(sk, flags & MSG_DONTWAIT);
	bool eor;
	size_t orig_size = size;
	unsigned char record_type = TLS_RECORD_TYPE_DATA;
	struct scatterlist *sg;
	bool full_record;
	int record_room;

	if (flags & ~(MSG_MORE | MSG_DONTWAIT | MSG_NOSIGNAL |
		      MSG_SENDPAGE_NOTLAST))
		return -ENOTSUPP;

	/* No MSG_EOR from splice, only look at MSG_MORE */
	eor = !(flags & (MSG_MORE | MSG_SENDPAGE_NOTLAST));

	lock_sock(sk);

	sk_clear_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	if (tls_complete_pending_work(sk, tls_ctx, flags, &timeo))
		goto sendpage_end;

	/* Call the sk_stream functions to manage the sndbuf mem. */
	while (size > 0) {
		size_t copy, required_size;

		if (sk->sk_err) {
			ret = -sk->sk_err;
			goto sendpage_end;
		}

		full_record = false;
		record_room = TLS_MAX_PAYLOAD_SIZE - ctx->sg_plaintext_size;
		copy = size;
		if (copy >= record_room) {
			copy = record_room;
			full_record = true;
		}
		required_size = ctx->sg_plaintext_size + copy +
			      tls_ctx->tx.overhead_size;

		if (!sk_stream_memory_free(sk))
			goto wait_for_sndbuf;
alloc_payload:
		ret = alloc_encrypted_sg(sk, required_size);
		if (ret) {
			if (ret != -ENOSPC)
				goto wait_for_memory;

			/* Adjust copy according to the amount that was
			 * actually allocated. The difference is due
			 * to max sg elements limit
			 */
			copy -= required_size - ctx->sg_plaintext_size;
			full_record = true;
		}

		get_page(page);
		sg = ctx->sg_plaintext_data + ctx->sg_plaintext_num_elem;
		sg_set_page(sg, page, copy, offset);
		sg_unmark_end(sg);

		ctx->sg_plaintext_num_elem++;

		sk_mem_charge(sk, copy);
		offset += copy;
		size -= copy;
		ctx->sg_plaintext_size += copy;
		tls_ctx->pending_open_record_frags = ctx->sg_plaintext_num_elem;

		if (full_record || eor ||
		    ctx->sg_plaintext_num_elem ==
		    ARRAY_SIZE(ctx->sg_plaintext_data)) {
push_record:
			ret = tls_push_record(sk, flags, record_type);
			if (ret) {
				if (ret == -ENOMEM)
					goto wait_for_memory;

				goto sendpage_end;
			}
		}
		continue;
wait_for_sndbuf:
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
wait_for_memory:
		ret = sk_stream_wait_memory(sk, &timeo);
		if (ret) {
			trim_both_sgl(sk, ctx->sg_plaintext_size);
			goto sendpage_end;
		}

		if (tls_is_pending_closed_record(tls_ctx))
			goto push_record;

		goto alloc_payload;
	}

sendpage_end:
	if (orig_size > size)
		ret = orig_size - size;
	else
		ret = sk_stream_error(sk, flags, ret);

	release_sock(sk);
	return ret;
}