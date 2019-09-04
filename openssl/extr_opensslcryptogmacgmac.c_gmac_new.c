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
struct TYPE_5__ {int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ EVP_MAC_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  gmac_free (TYPE_1__*) ; 

__attribute__((used)) static EVP_MAC_IMPL *gmac_new(void)
{
    EVP_MAC_IMPL *gctx;

    if ((gctx = OPENSSL_zalloc(sizeof(*gctx))) == NULL
        || (gctx->ctx = EVP_CIPHER_CTX_new()) == NULL) {
        gmac_free(gctx);
        return NULL;
    }
    return gctx;
}