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
struct tls_context {int /*<<< orphan*/  (* sk_write_space ) (struct sock*) ;scalar_t__ in_tcp_sendpages; } ;
struct sock {int /*<<< orphan*/  sk_allocation; int /*<<< orphan*/  sk_write_pending; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MSG_DONTWAIT ; 
 int MSG_NOSIGNAL ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 scalar_t__ tls_is_pending_closed_record (struct tls_context*) ; 
 int tls_push_pending_closed_record (struct sock*,struct tls_context*,int,long*) ; 

__attribute__((used)) static void tls_write_space(struct sock *sk)
{
	struct tls_context *ctx = tls_get_ctx(sk);

	/* If in_tcp_sendpages call lower protocol write space handler
	 * to ensure we wake up any waiting operations there. For example
	 * if do_tcp_sendpages where to call sk_wait_event.
	 */
	if (ctx->in_tcp_sendpages) {
		ctx->sk_write_space(sk);
		return;
	}

	if (!sk->sk_write_pending && tls_is_pending_closed_record(ctx)) {
		gfp_t sk_allocation = sk->sk_allocation;
		int rc;
		long timeo = 0;

		sk->sk_allocation = GFP_ATOMIC;
		rc = tls_push_pending_closed_record(sk, ctx,
						    MSG_DONTWAIT |
						    MSG_NOSIGNAL,
						    &timeo);
		sk->sk_allocation = sk_allocation;

		if (rc < 0)
			return;
	}

	ctx->sk_write_space(sk);
}