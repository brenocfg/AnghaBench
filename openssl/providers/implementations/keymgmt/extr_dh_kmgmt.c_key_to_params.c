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
 int /*<<< orphan*/  DH_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ * OSSL_PARAM_locate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_BN (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OSSL_PKEY_PARAM_DH_PRIV_KEY ; 
 int /*<<< orphan*/  OSSL_PKEY_PARAM_DH_PUB_KEY ; 
 int /*<<< orphan*/  domparams_to_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int key_to_params(DH *dh, OSSL_PARAM params[])
{
    OSSL_PARAM *p;
    const BIGNUM *priv_key = NULL, *pub_key = NULL;

    if (dh == NULL)
        return 0;
    if (!domparams_to_params(dh, params))
        return 0;

    DH_get0_key(dh, &pub_key, &priv_key);
    if ((p = OSSL_PARAM_locate(params,
                                     OSSL_PKEY_PARAM_DH_PRIV_KEY)) != NULL
        && !OSSL_PARAM_set_BN(p, priv_key))
        return 0;
    if ((p = OSSL_PARAM_locate(params,
                                     OSSL_PKEY_PARAM_DH_PUB_KEY)) != NULL
        && !OSSL_PARAM_set_BN(p, pub_key))
        return 0;

    return 1;
}