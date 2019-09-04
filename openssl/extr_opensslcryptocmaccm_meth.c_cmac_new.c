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
 int /*<<< orphan*/ * CMAC_CTX_new () ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

__attribute__((used)) static EVP_MAC_IMPL *cmac_new(void)
{
    EVP_MAC_IMPL *cctx;

    if ((cctx = OPENSSL_zalloc(sizeof(*cctx))) == NULL
        || (cctx->ctx = CMAC_CTX_new()) == NULL) {
        OPENSSL_free(cctx);
        cctx = NULL;
    }

    return cctx;
}