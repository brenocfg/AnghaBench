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
struct key_ctx {scalar_t__ implicit_iv_len; int /*<<< orphan*/ * hmac; int /*<<< orphan*/ * cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  cipher_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hmac_ctx_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hmac_ctx_free (int /*<<< orphan*/ *) ; 

void
free_key_ctx(struct key_ctx *ctx)
{
    if (ctx->cipher)
    {
        cipher_ctx_free(ctx->cipher);
        ctx->cipher = NULL;
    }
    if (ctx->hmac)
    {
        hmac_ctx_cleanup(ctx->hmac);
        hmac_ctx_free(ctx->hmac);
        ctx->hmac = NULL;
    }
    ctx->implicit_iv_len = 0;
}