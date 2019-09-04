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
struct TYPE_8__ {int /*<<< orphan*/ * (* new ) () ;} ;
struct TYPE_7__ {TYPE_2__ const* meth; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ EVP_MAC_CTX ;
typedef  TYPE_2__ EVP_MAC ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_F_EVP_MAC_CTX_NEW ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/ * stub1 () ; 

EVP_MAC_CTX *EVP_MAC_CTX_new(const EVP_MAC *mac)
{
    EVP_MAC_CTX *ctx = OPENSSL_zalloc(sizeof(EVP_MAC_CTX));

    if (ctx == NULL || (ctx->data = mac->new()) == NULL) {
        EVPerr(EVP_F_EVP_MAC_CTX_NEW, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(ctx);
        ctx = NULL;
    } else {
        ctx->meth = mac;
    }
    return ctx;
}