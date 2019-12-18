#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  engine; int /*<<< orphan*/  peerkey; int /*<<< orphan*/  pkey; int /*<<< orphan*/  keymgmt; TYPE_1__* pmeth; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* cleanup ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ EVP_PKEY_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_KEYMGMT_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 int /*<<< orphan*/  evp_pkey_ctx_free_old_ops (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void EVP_PKEY_CTX_free(EVP_PKEY_CTX *ctx)
{
    if (ctx == NULL)
        return;
    if (ctx->pmeth && ctx->pmeth->cleanup)
        ctx->pmeth->cleanup(ctx);

    evp_pkey_ctx_free_old_ops(ctx);
    EVP_KEYMGMT_free(ctx->keymgmt);

    EVP_PKEY_free(ctx->pkey);
    EVP_PKEY_free(ctx->peerkey);
#ifndef OPENSSL_NO_ENGINE
    ENGINE_finish(ctx->engine);
#endif
    OPENSSL_free(ctx);
}