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
struct tls_sw_context_rx {int /*<<< orphan*/  (* saved_data_ready ) (struct sock*) ;int /*<<< orphan*/  strp; } ;
struct tls_context {int dummy; } ;
struct sock {int dummy; } ;
struct sk_psock {int /*<<< orphan*/  ingress_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct sk_psock* sk_psock_get (struct sock*) ; 
 int /*<<< orphan*/  sk_psock_put (struct sock*,struct sk_psock*) ; 
 int /*<<< orphan*/  strp_data_ready (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_sw_context_rx* tls_sw_ctx_rx (struct tls_context*) ; 

__attribute__((used)) static void tls_data_ready(struct sock *sk)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);
	struct sk_psock *psock;

	strp_data_ready(&ctx->strp);

	psock = sk_psock_get(sk);
	if (psock && !list_empty(&psock->ingress_msg)) {
		ctx->saved_data_ready(sk);
		sk_psock_put(sk, psock);
	}
}