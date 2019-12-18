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
struct tls_context {void* rx_conf; void* tx_conf; } ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_callback_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTSUPP ; 
 scalar_t__ TCP_ESTABLISHED ; 
 void* TLS_BASE ; 
 struct tls_context* create_ctx (struct sock*) ; 
 int /*<<< orphan*/  tls_build_proto (struct sock*) ; 
 scalar_t__ tls_hw_prot (struct sock*) ; 
 int /*<<< orphan*/  update_sk_prot (struct sock*,struct tls_context*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tls_init(struct sock *sk)
{
	struct tls_context *ctx;
	int rc = 0;

	if (tls_hw_prot(sk))
		return 0;

	/* The TLS ulp is currently supported only for TCP sockets
	 * in ESTABLISHED state.
	 * Supporting sockets in LISTEN state will require us
	 * to modify the accept implementation to clone rather then
	 * share the ulp context.
	 */
	if (sk->sk_state != TCP_ESTABLISHED)
		return -ENOTSUPP;

	tls_build_proto(sk);

	/* allocate tls context */
	write_lock_bh(&sk->sk_callback_lock);
	ctx = create_ctx(sk);
	if (!ctx) {
		rc = -ENOMEM;
		goto out;
	}

	ctx->tx_conf = TLS_BASE;
	ctx->rx_conf = TLS_BASE;
	update_sk_prot(sk, ctx);
out:
	write_unlock_bh(&sk->sk_callback_lock);
	return rc;
}