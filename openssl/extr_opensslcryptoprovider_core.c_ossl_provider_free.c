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
struct TYPE_4__ {int /*<<< orphan*/  refcnt_lock; int /*<<< orphan*/  parameters; struct TYPE_4__* path; struct TYPE_4__* name; int /*<<< orphan*/  module; scalar_t__ flag_initialized; int /*<<< orphan*/  provctx; int /*<<< orphan*/  (* teardown ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_1__ OSSL_PROVIDER ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_DOWN_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSO_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_infopair ; 
 int /*<<< orphan*/  sk_INFOPAIR_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void ossl_provider_free(OSSL_PROVIDER *prov)
{
    if (prov != NULL) {
        int ref = 0;

        CRYPTO_DOWN_REF(&prov->refcnt, &ref, prov->refcnt_lock);

        /*
         * When the refcount drops below two, the store is the only
         * possible reference, or it has already been taken away from
         * the store (this may happen if a provider was activated
         * because it's a fallback, but isn't currently used)
         * When that happens, the provider is inactivated.
         */
        if (ref < 2 && prov->flag_initialized) {
            if (prov->teardown != NULL)
                prov->teardown(prov->provctx);
            prov->flag_initialized = 0;
        }

        /*
         * When the refcount drops to zero, it has been taken out of
         * the store.  All we have to do here is clean it out.
         */
        if (ref == 0) {
            DSO_free(prov->module);
            OPENSSL_free(prov->name);
            OPENSSL_free(prov->path);
            sk_INFOPAIR_pop_free(prov->parameters, free_infopair);
#ifndef HAVE_ATOMICS
            CRYPTO_THREAD_lock_free(prov->refcnt_lock);
#endif
            OPENSSL_free(prov);
        }
    }
}