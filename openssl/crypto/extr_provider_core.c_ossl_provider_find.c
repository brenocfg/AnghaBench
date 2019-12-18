#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct provider_store_st {int /*<<< orphan*/  lock; int /*<<< orphan*/  providers; } ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_INIT_LOAD_CONFIG ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct provider_store_st* get_provider_store (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_provider_up_ref (TYPE_1__*) ; 
 int sk_OSSL_PROVIDER_find (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* sk_OSSL_PROVIDER_value (int /*<<< orphan*/ ,int) ; 

OSSL_PROVIDER *ossl_provider_find(OPENSSL_CTX *libctx, const char *name,
                                  int noconfig)
{
    struct provider_store_st *store = NULL;
    OSSL_PROVIDER *prov = NULL;

    if ((store = get_provider_store(libctx)) != NULL) {
        OSSL_PROVIDER tmpl = { 0, };
        int i;

#ifndef FIPS_MODE
        /*
         * Make sure any providers are loaded from config before we try to find
         * them.
         */
        if (!noconfig)
            OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CONFIG, NULL);
#endif

        tmpl.name = (char *)name;
        CRYPTO_THREAD_write_lock(store->lock);
        if ((i = sk_OSSL_PROVIDER_find(store->providers, &tmpl)) == -1
            || (prov = sk_OSSL_PROVIDER_value(store->providers, i)) == NULL
            || !ossl_provider_up_ref(prov))
            prov = NULL;
        CRYPTO_THREAD_unlock(store->lock);
    }

    return prov;
}