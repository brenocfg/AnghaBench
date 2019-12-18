#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * dsa; } ;
struct TYPE_5__ {TYPE_1__ pkey; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM_BLD ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_KEYMGMT ;
typedef  int /*<<< orphan*/  DSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * DSA_get0_g (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DSA_get0_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DSA_get0_priv_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DSA_get0_pub_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DSA_get0_q (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_PKEY_PARAM_DSA_PRIV_KEY ; 
 int /*<<< orphan*/  OSSL_PKEY_PARAM_DSA_PUB_KEY ; 
 int /*<<< orphan*/  OSSL_PKEY_PARAM_FFC_G ; 
 int /*<<< orphan*/  OSSL_PKEY_PARAM_FFC_P ; 
 int /*<<< orphan*/  OSSL_PKEY_PARAM_FFC_Q ; 
 void* evp_keymgmt_importdomparams (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* evp_keymgmt_importkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_param_bld_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_param_bld_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_param_bld_push_BN (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ossl_param_bld_to_param (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *dsa_pkey_export_to(const EVP_PKEY *pk, EVP_KEYMGMT *keymgmt,
                                int want_domainparams)
{
    DSA *dsa = pk->pkey.dsa;
    OSSL_PARAM_BLD tmpl;
    const BIGNUM *p = DSA_get0_p(dsa), *g = DSA_get0_g(dsa);
    const BIGNUM *q = DSA_get0_q(dsa), *pub_key = DSA_get0_pub_key(dsa);
    const BIGNUM *priv_key = DSA_get0_priv_key(dsa);
    OSSL_PARAM *params;
    void *provdata = NULL;

    if (p == NULL || q == NULL || g == NULL)
        return NULL;

    ossl_param_bld_init(&tmpl);
    if (!ossl_param_bld_push_BN(&tmpl, OSSL_PKEY_PARAM_FFC_P, p)
        || !ossl_param_bld_push_BN(&tmpl, OSSL_PKEY_PARAM_FFC_Q, q)
        || !ossl_param_bld_push_BN(&tmpl, OSSL_PKEY_PARAM_FFC_G, g))
        return NULL;

    if (!want_domainparams) {
        /* A key must at least have a public part. */
        if (!ossl_param_bld_push_BN(&tmpl, OSSL_PKEY_PARAM_DSA_PUB_KEY,
                                    pub_key))
            return NULL;

        if (priv_key != NULL) {
            if (!ossl_param_bld_push_BN(&tmpl, OSSL_PKEY_PARAM_DSA_PRIV_KEY,
                                        priv_key))
                return NULL;
        }
    }

    params = ossl_param_bld_to_param(&tmpl);

    /* We export, the provider imports */
    provdata = want_domainparams
        ? evp_keymgmt_importdomparams(keymgmt, params)
        : evp_keymgmt_importkey(keymgmt, params);

    ossl_param_bld_free(params);
    return provdata;
}