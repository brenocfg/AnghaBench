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
struct tls_sw_context_tx {int /*<<< orphan*/  sg_plaintext_size; int /*<<< orphan*/  sg_plaintext_num_elem; int /*<<< orphan*/  sg_plaintext_data; int /*<<< orphan*/  sg_encrypted_size; int /*<<< orphan*/  sg_encrypted_num_elem; int /*<<< orphan*/  sg_encrypted_data; } ;
struct tls_context {int dummy; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_sg (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_sw_context_tx* tls_sw_ctx_tx (struct tls_context*) ; 

__attribute__((used)) static void tls_free_both_sg(struct sock *sk)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);

	free_sg(sk, ctx->sg_encrypted_data, &ctx->sg_encrypted_num_elem,
		&ctx->sg_encrypted_size);

	free_sg(sk, ctx->sg_plaintext_data, &ctx->sg_plaintext_num_elem,
		&ctx->sg_plaintext_size);
}