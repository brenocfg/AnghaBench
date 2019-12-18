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
struct tls_sw_context_rx {int /*<<< orphan*/  rx_list; scalar_t__ recv_pkt; } ;
struct tls_context {int dummy; } ;
struct sock {int dummy; } ;
struct sk_psock {int /*<<< orphan*/  ingress_msg; } ;

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct sk_psock* sk_psock (struct sock const*) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 struct tls_context* tls_get_ctx (struct sock const*) ; 
 struct tls_sw_context_rx* tls_sw_ctx_rx (struct tls_context*) ; 

bool tls_sw_stream_read(const struct sock *sk)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);
	bool ingress_empty = true;
	struct sk_psock *psock;

	rcu_read_lock();
	psock = sk_psock(sk);
	if (psock)
		ingress_empty = list_empty(&psock->ingress_msg);
	rcu_read_unlock();

	return !ingress_empty || ctx->recv_pkt ||
		!skb_queue_empty(&ctx->rx_list);
}