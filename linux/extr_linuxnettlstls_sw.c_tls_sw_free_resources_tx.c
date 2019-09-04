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
struct tls_sw_context_tx {int /*<<< orphan*/  aead_send; } ;
struct tls_context {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_aead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tls_sw_context_tx*) ; 
 int /*<<< orphan*/  tls_free_both_sg (struct sock*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_sw_context_tx* tls_sw_ctx_tx (struct tls_context*) ; 

void tls_sw_free_resources_tx(struct sock *sk)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);

	crypto_free_aead(ctx->aead_send);
	tls_free_both_sg(sk);

	kfree(ctx);
}