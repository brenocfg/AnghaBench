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
struct tls_context {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  crypto_recv; int /*<<< orphan*/  crypto_send; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tls_context*) ; 
 int /*<<< orphan*/  kfree_rcu (struct tls_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memzero_explicit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 

void tls_ctx_free(struct sock *sk, struct tls_context *ctx)
{
	if (!ctx)
		return;

	memzero_explicit(&ctx->crypto_send, sizeof(ctx->crypto_send));
	memzero_explicit(&ctx->crypto_recv, sizeof(ctx->crypto_recv));
	mutex_destroy(&ctx->tx_lock);

	if (sk)
		kfree_rcu(ctx, rcu);
	else
		kfree(ctx);
}