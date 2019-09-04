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
struct tls_sw_context_tx {int /*<<< orphan*/  sg_encrypted_size; int /*<<< orphan*/  sg_encrypted_num_elem; int /*<<< orphan*/  sg_encrypted_data; int /*<<< orphan*/  sg_plaintext_size; int /*<<< orphan*/  sg_plaintext_num_elem; int /*<<< orphan*/  sg_plaintext_data; } ;
struct TYPE_2__ {scalar_t__ overhead_size; } ;
struct tls_context {TYPE_1__ tx; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_sw_context_tx* tls_sw_ctx_tx (struct tls_context*) ; 
 int /*<<< orphan*/  trim_sg (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void trim_both_sgl(struct sock *sk, int target_size)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);

	trim_sg(sk, ctx->sg_plaintext_data,
		&ctx->sg_plaintext_num_elem,
		&ctx->sg_plaintext_size,
		target_size);

	if (target_size > 0)
		target_size += tls_ctx->tx.overhead_size;

	trim_sg(sk, ctx->sg_encrypted_data,
		&ctx->sg_encrypted_num_elem,
		&ctx->sg_encrypted_size,
		target_size);
}