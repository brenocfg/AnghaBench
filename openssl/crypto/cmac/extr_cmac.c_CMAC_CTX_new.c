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
struct TYPE_5__ {int nlast_block; int /*<<< orphan*/ * cctx; } ;
typedef  TYPE_1__ CMAC_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_CMAC_CTX_NEW ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_malloc (int) ; 

CMAC_CTX *CMAC_CTX_new(void)
{
    CMAC_CTX *ctx;

    if ((ctx = OPENSSL_malloc(sizeof(*ctx))) == NULL) {
        CRYPTOerr(CRYPTO_F_CMAC_CTX_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    ctx->cctx = EVP_CIPHER_CTX_new();
    if (ctx->cctx == NULL) {
        OPENSSL_free(ctx);
        return NULL;
    }
    ctx->nlast_block = -1;
    return ctx;
}