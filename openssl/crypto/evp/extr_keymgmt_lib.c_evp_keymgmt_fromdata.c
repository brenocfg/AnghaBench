#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* (* importkey ) (void*,int /*<<< orphan*/  const*) ;void* (* importdomparams ) (void*,int /*<<< orphan*/  const*) ;} ;
struct TYPE_10__ {TYPE_1__* pkeys; } ;
struct TYPE_9__ {int domainparams; void* provdata; TYPE_3__* keymgmt; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  TYPE_3__ EVP_KEYMGMT ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_KEYMGMT_provider (TYPE_3__*) ; 
 int /*<<< orphan*/  EVP_KEYMGMT_up_ref (TYPE_3__*) ; 
 int /*<<< orphan*/  evp_keymgmt_clear_pkey_cache (TYPE_2__*) ; 
 void* ossl_provider_ctx (int /*<<< orphan*/ ) ; 
 void* stub1 (void*,int /*<<< orphan*/  const*) ; 
 void* stub2 (void*,int /*<<< orphan*/  const*) ; 

void *evp_keymgmt_fromdata(EVP_PKEY *target, EVP_KEYMGMT *keymgmt,
                           const OSSL_PARAM params[], int domainparams)
{
    void *provctx = ossl_provider_ctx(EVP_KEYMGMT_provider(keymgmt));
    void *provdata = domainparams
        ? keymgmt->importdomparams(provctx, params)
        : keymgmt->importkey(provctx, params);

    evp_keymgmt_clear_pkey_cache(target);
    if (provdata != NULL) {
        EVP_KEYMGMT_up_ref(keymgmt);
        target->pkeys[0].keymgmt = keymgmt;
        target->pkeys[0].provdata = provdata;
        target->pkeys[0].domainparams = domainparams;
    }

    return provdata;
}