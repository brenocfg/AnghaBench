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
struct TYPE_3__ {int /*<<< orphan*/  key; scalar_t__ key_length; int /*<<< orphan*/ * md; int /*<<< orphan*/  md_ctx; int /*<<< orphan*/  o_ctx; int /*<<< orphan*/  i_ctx; } ;
typedef  TYPE_1__ HMAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_CTX_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hmac_ctx_cleanup(HMAC_CTX *ctx)
{
    EVP_MD_CTX_reset(ctx->i_ctx);
    EVP_MD_CTX_reset(ctx->o_ctx);
    EVP_MD_CTX_reset(ctx->md_ctx);
    ctx->md = NULL;
    ctx->key_length = 0;
    OPENSSL_cleanse(ctx->key, sizeof(ctx->key));
}