#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  md_ctx; int /*<<< orphan*/  o_ctx; int /*<<< orphan*/  i_ctx; } ;
typedef  TYPE_1__ HMAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  hmac_ctx_cleanup (TYPE_1__*) ; 

void HMAC_CTX_free(HMAC_CTX *ctx)
{
    if (ctx != NULL) {
        hmac_ctx_cleanup(ctx);
        EVP_MD_CTX_free(ctx->i_ctx);
        EVP_MD_CTX_free(ctx->o_ctx);
        EVP_MD_CTX_free(ctx->md_ctx);
        OPENSSL_free(ctx);
    }
}