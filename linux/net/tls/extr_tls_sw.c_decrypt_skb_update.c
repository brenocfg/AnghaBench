#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tls_sw_context_rx {int decrypted; int /*<<< orphan*/  (* saved_data_ready ) (struct sock*) ;} ;
struct tls_prot_info {scalar_t__ overhead_size; scalar_t__ prepend_size; } ;
struct tls_context {scalar_t__ rx_conf; int /*<<< orphan*/  rx; struct tls_prot_info prot_info; } ;
struct strp_msg {int full_len; int /*<<< orphan*/  offset; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct iov_iter {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 scalar_t__ TLS_HW ; 
 int decrypt_internal (struct sock*,struct sk_buff*,struct iov_iter*,int /*<<< orphan*/ *,int*,int*,int) ; 
 int padding_length (struct tls_sw_context_rx*,struct tls_prot_info*,struct sk_buff*) ; 
 struct strp_msg* strp_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tls_advance_record_sn (struct sock*,struct tls_prot_info*,int /*<<< orphan*/ *) ; 
 int tls_device_decrypted (struct sock*,struct sk_buff*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_sw_context_rx* tls_sw_ctx_rx (struct tls_context*) ; 

__attribute__((used)) static int decrypt_skb_update(struct sock *sk, struct sk_buff *skb,
			      struct iov_iter *dest, int *chunk, bool *zc,
			      bool async)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);
	struct tls_prot_info *prot = &tls_ctx->prot_info;
	struct strp_msg *rxm = strp_msg(skb);
	int pad, err = 0;

	if (!ctx->decrypted) {
		if (tls_ctx->rx_conf == TLS_HW) {
			err = tls_device_decrypted(sk, skb);
			if (err < 0)
				return err;
		}

		/* Still not decrypted after tls_device */
		if (!ctx->decrypted) {
			err = decrypt_internal(sk, skb, dest, NULL, chunk, zc,
					       async);
			if (err < 0) {
				if (err == -EINPROGRESS)
					tls_advance_record_sn(sk, prot,
							      &tls_ctx->rx);

				return err;
			}
		} else {
			*zc = false;
		}

		pad = padding_length(ctx, prot, skb);
		if (pad < 0)
			return pad;

		rxm->full_len -= pad;
		rxm->offset += prot->prepend_size;
		rxm->full_len -= prot->overhead_size;
		tls_advance_record_sn(sk, prot, &tls_ctx->rx);
		ctx->decrypted = true;
		ctx->saved_data_ready(sk);
	} else {
		*zc = false;
	}

	return err;
}