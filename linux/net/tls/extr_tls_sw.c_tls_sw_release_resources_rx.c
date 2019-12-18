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
struct tls_sw_context_rx {scalar_t__ saved_data_ready; int /*<<< orphan*/  strp; scalar_t__ aead_recv; int /*<<< orphan*/  rx_list; int /*<<< orphan*/ * recv_pkt; } ;
struct TYPE_2__ {int /*<<< orphan*/  iv; int /*<<< orphan*/  rec_seq; } ;
struct tls_context {TYPE_1__ rx; } ;
struct sock {int /*<<< orphan*/  sk_callback_lock; scalar_t__ sk_data_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_aead (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strp_stop (int /*<<< orphan*/ *) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_sw_context_rx* tls_sw_ctx_rx (struct tls_context*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void tls_sw_release_resources_rx(struct sock *sk)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);

	kfree(tls_ctx->rx.rec_seq);
	kfree(tls_ctx->rx.iv);

	if (ctx->aead_recv) {
		kfree_skb(ctx->recv_pkt);
		ctx->recv_pkt = NULL;
		skb_queue_purge(&ctx->rx_list);
		crypto_free_aead(ctx->aead_recv);
		strp_stop(&ctx->strp);
		/* If tls_sw_strparser_arm() was not called (cleanup paths)
		 * we still want to strp_stop(), but sk->sk_data_ready was
		 * never swapped.
		 */
		if (ctx->saved_data_ready) {
			write_lock_bh(&sk->sk_callback_lock);
			sk->sk_data_ready = ctx->saved_data_ready;
			write_unlock_bh(&sk->sk_callback_lock);
		}
	}
}