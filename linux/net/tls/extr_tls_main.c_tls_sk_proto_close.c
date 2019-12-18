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
struct tls_context {scalar_t__ tx_conf; scalar_t__ rx_conf; scalar_t__ sk_write_space; TYPE_1__* sk_proto; } ;
struct sock {scalar_t__ sk_write_space; int /*<<< orphan*/  sk_callback_lock; TYPE_1__* sk_prot; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_ulp_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct sock*,long) ;} ;

/* Variables and functions */
 scalar_t__ TLS_BASE ; 
 scalar_t__ TLS_HW ; 
 scalar_t__ TLS_SW ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 long sock_sndtimeo (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*,long) ; 
 int /*<<< orphan*/  tls_ctx_free (struct sock*,struct tls_context*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 int /*<<< orphan*/  tls_sk_proto_cleanup (struct sock*,struct tls_context*,long) ; 
 int /*<<< orphan*/  tls_sw_cancel_work_tx (struct tls_context*) ; 
 int /*<<< orphan*/  tls_sw_free_ctx_rx (struct tls_context*) ; 
 int /*<<< orphan*/  tls_sw_free_ctx_tx (struct tls_context*) ; 
 int /*<<< orphan*/  tls_sw_strparser_done (struct tls_context*) ; 
 scalar_t__ tls_write_space ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tls_sk_proto_close(struct sock *sk, long timeout)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tls_context *ctx = tls_get_ctx(sk);
	long timeo = sock_sndtimeo(sk, 0);
	bool free_ctx;

	if (ctx->tx_conf == TLS_SW)
		tls_sw_cancel_work_tx(ctx);

	lock_sock(sk);
	free_ctx = ctx->tx_conf != TLS_HW && ctx->rx_conf != TLS_HW;

	if (ctx->tx_conf != TLS_BASE || ctx->rx_conf != TLS_BASE)
		tls_sk_proto_cleanup(sk, ctx, timeo);

	write_lock_bh(&sk->sk_callback_lock);
	if (free_ctx)
		rcu_assign_pointer(icsk->icsk_ulp_data, NULL);
	sk->sk_prot = ctx->sk_proto;
	if (sk->sk_write_space == tls_write_space)
		sk->sk_write_space = ctx->sk_write_space;
	write_unlock_bh(&sk->sk_callback_lock);
	release_sock(sk);
	if (ctx->tx_conf == TLS_SW)
		tls_sw_free_ctx_tx(ctx);
	if (ctx->rx_conf == TLS_SW || ctx->rx_conf == TLS_HW)
		tls_sw_strparser_done(ctx);
	if (ctx->rx_conf == TLS_SW)
		tls_sw_free_ctx_rx(ctx);
	ctx->sk_proto->close(sk, timeout);

	if (free_ctx)
		tls_ctx_free(sk, ctx);
}