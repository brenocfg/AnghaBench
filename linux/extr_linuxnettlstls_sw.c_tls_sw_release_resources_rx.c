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
struct tls_sw_context_rx {int /*<<< orphan*/  strp; int /*<<< orphan*/  saved_data_ready; scalar_t__ aead_recv; int /*<<< orphan*/ * recv_pkt; } ;
struct tls_context {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_data_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_aead (scalar_t__) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  strp_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strp_stop (int /*<<< orphan*/ *) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_sw_context_rx* tls_sw_ctx_rx (struct tls_context*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void tls_sw_release_resources_rx(struct sock *sk)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);

	if (ctx->aead_recv) {
		kfree_skb(ctx->recv_pkt);
		ctx->recv_pkt = NULL;
		crypto_free_aead(ctx->aead_recv);
		strp_stop(&ctx->strp);
		write_lock_bh(&sk->sk_callback_lock);
		sk->sk_data_ready = ctx->saved_data_ready;
		write_unlock_bh(&sk->sk_callback_lock);
		release_sock(sk);
		strp_done(&ctx->strp);
		lock_sock(sk);
	}
}