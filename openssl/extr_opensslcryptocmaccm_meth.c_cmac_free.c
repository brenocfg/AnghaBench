#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ EVP_MAC_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/  CMAC_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

__attribute__((used)) static void cmac_free(EVP_MAC_IMPL *cctx)
{
    if (cctx != NULL) {
        CMAC_CTX_free(cctx->ctx);
        OPENSSL_free(cctx);
    }
}