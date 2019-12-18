#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* freectx ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {TYPE_3__* meth; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ EVP_KDF_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KDF_free (TYPE_3__*) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void EVP_KDF_CTX_free(EVP_KDF_CTX *ctx)
{
    if (ctx != NULL) {
        ctx->meth->freectx(ctx->data);
        ctx->data = NULL;
        EVP_KDF_free(ctx->meth);
        OPENSSL_free(ctx);
    }
}