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
struct tls_context {int /*<<< orphan*/  (* sk_destruct ) (struct sock*) ;} ;
struct sock {int dummy; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_ulp_data; } ;

/* Variables and functions */
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tls_ctx_free (struct sock*,struct tls_context*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 

__attribute__((used)) static void tls_hw_sk_destruct(struct sock *sk)
{
	struct tls_context *ctx = tls_get_ctx(sk);
	struct inet_connection_sock *icsk = inet_csk(sk);

	ctx->sk_destruct(sk);
	/* Free ctx */
	rcu_assign_pointer(icsk->icsk_ulp_data, NULL);
	tls_ctx_free(sk, ctx);
}