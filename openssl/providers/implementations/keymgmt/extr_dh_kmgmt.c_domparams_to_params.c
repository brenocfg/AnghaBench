#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  DH_get0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ * OSSL_PARAM_locate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_BN (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OSSL_PKEY_PARAM_FFC_G ; 
 int /*<<< orphan*/  OSSL_PKEY_PARAM_FFC_P ; 

__attribute__((used)) static int domparams_to_params(DH *dh, OSSL_PARAM params[])
{
    OSSL_PARAM *p;
    const BIGNUM *dh_p = NULL, *dh_g = NULL;

    if (dh == NULL)
        return 0;

    DH_get0_pqg(dh, &dh_p, NULL, &dh_g);
    if ((p = OSSL_PARAM_locate(params, OSSL_PKEY_PARAM_FFC_P)) != NULL
        && !OSSL_PARAM_set_BN(p, dh_p))
        return 0;
    if ((p = OSSL_PARAM_locate(params, OSSL_PKEY_PARAM_FFC_G)) != NULL
        && !OSSL_PARAM_set_BN(p, dh_g))
        return 0;

    return 1;
}