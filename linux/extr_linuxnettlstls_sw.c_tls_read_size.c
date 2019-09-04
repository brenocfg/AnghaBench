#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tls_sw_context_rx {char control; } ;
struct TYPE_5__ {int /*<<< orphan*/  version; } ;
struct TYPE_6__ {TYPE_2__ info; } ;
struct TYPE_4__ {int prepend_size; size_t tag_size; size_t iv_size; } ;
struct tls_context {TYPE_3__ crypto_recv; TYPE_1__ rx; } ;
struct strparser {int /*<<< orphan*/  sk; } ;
struct strp_msg {scalar_t__ offset; } ;
struct sk_buff {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  header ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int MAX_IV_SIZE ; 
 int TLS_HEADER_SIZE ; 
 size_t TLS_MAX_PAYLOAD_SIZE ; 
 char TLS_VERSION_MAJOR (int /*<<< orphan*/ ) ; 
 char TLS_VERSION_MINOR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int skb_copy_bits (struct sk_buff*,scalar_t__,char*,int) ; 
 struct strp_msg* strp_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  tls_err_abort (int /*<<< orphan*/ ,int) ; 
 struct tls_context* tls_get_ctx (int /*<<< orphan*/ ) ; 
 struct tls_sw_context_rx* tls_sw_ctx_rx (struct tls_context*) ; 

__attribute__((used)) static int tls_read_size(struct strparser *strp, struct sk_buff *skb)
{
	struct tls_context *tls_ctx = tls_get_ctx(strp->sk);
	struct tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);
	char header[TLS_HEADER_SIZE + MAX_IV_SIZE];
	struct strp_msg *rxm = strp_msg(skb);
	size_t cipher_overhead;
	size_t data_len = 0;
	int ret;

	/* Verify that we have a full TLS header, or wait for more data */
	if (rxm->offset + tls_ctx->rx.prepend_size > skb->len)
		return 0;

	/* Sanity-check size of on-stack buffer. */
	if (WARN_ON(tls_ctx->rx.prepend_size > sizeof(header))) {
		ret = -EINVAL;
		goto read_failure;
	}

	/* Linearize header to local buffer */
	ret = skb_copy_bits(skb, rxm->offset, header, tls_ctx->rx.prepend_size);

	if (ret < 0)
		goto read_failure;

	ctx->control = header[0];

	data_len = ((header[4] & 0xFF) | (header[3] << 8));

	cipher_overhead = tls_ctx->rx.tag_size + tls_ctx->rx.iv_size;

	if (data_len > TLS_MAX_PAYLOAD_SIZE + cipher_overhead) {
		ret = -EMSGSIZE;
		goto read_failure;
	}
	if (data_len < cipher_overhead) {
		ret = -EBADMSG;
		goto read_failure;
	}

	if (header[1] != TLS_VERSION_MINOR(tls_ctx->crypto_recv.info.version) ||
	    header[2] != TLS_VERSION_MAJOR(tls_ctx->crypto_recv.info.version)) {
		ret = -EINVAL;
		goto read_failure;
	}

#ifdef CONFIG_TLS_DEVICE
	handle_device_resync(strp->sk, TCP_SKB_CB(skb)->seq + rxm->offset,
			     *(u64*)tls_ctx->rx.rec_seq);
#endif
	return data_len + TLS_HEADER_SIZE;

read_failure:
	tls_err_abort(strp->sk, ret);

	return ret;
}