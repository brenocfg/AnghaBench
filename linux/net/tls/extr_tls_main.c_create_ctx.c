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
struct tls_context {int /*<<< orphan*/  sk_proto; int /*<<< orphan*/  tx_lock; } ;
struct sock {int /*<<< orphan*/  sk_prot; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_ulp_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 struct tls_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct tls_context*) ; 

__attribute__((used)) static struct tls_context *create_ctx(struct sock *sk)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tls_context *ctx;

	ctx = kzalloc(sizeof(*ctx), GFP_ATOMIC);
	if (!ctx)
		return NULL;

	mutex_init(&ctx->tx_lock);
	rcu_assign_pointer(icsk->icsk_ulp_data, ctx);
	ctx->sk_proto = sk->sk_prot;
	return ctx;
}