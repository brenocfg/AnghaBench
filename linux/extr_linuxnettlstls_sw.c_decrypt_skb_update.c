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
struct tls_sw_context_rx {int decrypted; int /*<<< orphan*/  (* saved_data_ready ) (struct sock*) ;} ;
struct TYPE_2__ {scalar_t__ overhead_size; scalar_t__ prepend_size; } ;
struct tls_context {TYPE_1__ rx; } ;
struct strp_msg {int /*<<< orphan*/  full_len; int /*<<< orphan*/  offset; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct iov_iter {int dummy; } ;

/* Variables and functions */
 int decrypt_internal (struct sock*,struct sk_buff*,struct iov_iter*,int /*<<< orphan*/ *,int*,int*) ; 
 struct strp_msg* strp_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tls_advance_record_sn (struct sock*,TYPE_1__*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_sw_context_rx* tls_sw_ctx_rx (struct tls_context*) ; 

__attribute__((used)) static int decrypt_skb_update(struct sock *sk, struct sk_buff *skb,
			      struct iov_iter *dest, int *chunk, bool *zc)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);
	struct strp_msg *rxm = strp_msg(skb);
	int err = 0;

#ifdef CONFIG_TLS_DEVICE
	err = tls_device_decrypted(sk, skb);
	if (err < 0)
		return err;
#endif
	if (!ctx->decrypted) {
		err = decrypt_internal(sk, skb, dest, NULL, chunk, zc);
		if (err < 0)
			return err;
	} else {
		*zc = false;
	}

	rxm->offset += tls_ctx->rx.prepend_size;
	rxm->full_len -= tls_ctx->rx.overhead_size;
	tls_advance_record_sn(sk, &tls_ctx->rx);
	ctx->decrypted = true;
	ctx->saved_data_ready(sk);

	return err;
}