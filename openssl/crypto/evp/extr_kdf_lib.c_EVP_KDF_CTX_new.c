#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  (* freectx ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  prov; int /*<<< orphan*/ * (* newctx ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_2__* meth; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ EVP_KDF_CTX ;
typedef  TYPE_2__ EVP_KDF ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_F_EVP_KDF_CTX_NEW ; 
 int /*<<< orphan*/  EVP_KDF_up_ref (TYPE_2__*) ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  ossl_provider_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

EVP_KDF_CTX *EVP_KDF_CTX_new(EVP_KDF *kdf)
{
    EVP_KDF_CTX *ctx = NULL;

    if (kdf == NULL)
        return NULL;

    ctx = OPENSSL_zalloc(sizeof(EVP_KDF_CTX));
    if (ctx == NULL
        || (ctx->data = kdf->newctx(ossl_provider_ctx(kdf->prov))) == NULL
        || !EVP_KDF_up_ref(kdf)) {
        EVPerr(EVP_F_EVP_KDF_CTX_NEW, ERR_R_MALLOC_FAILURE);
        if (ctx != NULL)
            kdf->freectx(ctx->data);
        OPENSSL_free(ctx);
        ctx = NULL;
    } else {
        ctx->meth = kdf;
    }
    return ctx;
}