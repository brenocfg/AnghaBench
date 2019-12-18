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
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_3__ {int /*<<< orphan*/ * validatedSrvCert; } ;
typedef  TYPE_1__ OSSL_CMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_assert (int /*<<< orphan*/ ) ; 

int ossl_cmp_ctx_set0_validatedSrvCert(OSSL_CMP_CTX *ctx, X509 *cert)
{
    if (!ossl_assert(ctx != NULL))
        return 0;
    X509_free(ctx->validatedSrvCert);
    ctx->validatedSrvCert = cert;
    return 1;
}