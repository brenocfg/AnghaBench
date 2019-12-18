#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  iv_len; int /*<<< orphan*/  iv; int /*<<< orphan*/  ki_len; int /*<<< orphan*/  ki; int /*<<< orphan*/  label_len; int /*<<< orphan*/  label; int /*<<< orphan*/  context_len; int /*<<< orphan*/  context; int /*<<< orphan*/  ctx_init; } ;
typedef  TYPE_1__ KBKDF ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MAC_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kbkdf_reset(void *vctx)
{
    KBKDF *ctx = (KBKDF *)vctx;

    EVP_MAC_CTX_free(ctx->ctx_init);
    OPENSSL_clear_free(ctx->context, ctx->context_len);
    OPENSSL_clear_free(ctx->label, ctx->label_len);
    OPENSSL_clear_free(ctx->ki, ctx->ki_len);
    OPENSSL_clear_free(ctx->iv, ctx->iv_len);
    memset(ctx, 0, sizeof(*ctx));
}