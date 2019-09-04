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
struct tls_sw_context_tx {int /*<<< orphan*/  sg_plaintext_data; int /*<<< orphan*/  sg_plaintext_num_elem; int /*<<< orphan*/  sg_plaintext_size; } ;
struct tls_context {int /*<<< orphan*/  pending_open_record_frags; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOSPC ; 
 int sk_alloc_sg (struct sock*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_sw_context_tx* tls_sw_ctx_tx (struct tls_context*) ; 

__attribute__((used)) static int alloc_plaintext_sg(struct sock *sk, int len)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_tx *ctx = tls_sw_ctx_tx(tls_ctx);
	int rc = 0;

	rc = sk_alloc_sg(sk, len, ctx->sg_plaintext_data, 0,
			 &ctx->sg_plaintext_num_elem, &ctx->sg_plaintext_size,
			 tls_ctx->pending_open_record_frags);

	if (rc == -ENOSPC)
		ctx->sg_plaintext_num_elem = ARRAY_SIZE(ctx->sg_plaintext_data);

	return rc;
}