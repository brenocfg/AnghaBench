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
struct TYPE_3__ {int /*<<< orphan*/  const* prov; } ;
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_1__ FIPS_GLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_CTX_FIPS_PROV_INDEX ; 
 int /*<<< orphan*/  fips_prov_ossl_ctx_method ; 
 TYPE_1__* openssl_ctx_get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const OSSL_PROVIDER *FIPS_get_provider(OPENSSL_CTX *ctx)
{
    FIPS_GLOBAL *fgbl = openssl_ctx_get_data(ctx, OPENSSL_CTX_FIPS_PROV_INDEX,
                                             &fips_prov_ossl_ctx_method);

    if (fgbl == NULL)
        return NULL;

    return fgbl->prov;
}