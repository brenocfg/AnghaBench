#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct provider_store_st {int /*<<< orphan*/  lock; int /*<<< orphan*/  providers; } ;
struct TYPE_8__ {struct provider_store_st* store; } ;
typedef  int /*<<< orphan*/  OSSL_provider_init_fn ;
typedef  TYPE_1__ OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_F_OSSL_PROVIDER_NEW ; 
 int /*<<< orphan*/  CRYPTO_R_PROVIDER_ALREADY_EXISTS ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char const*) ; 
 struct provider_store_st* get_provider_store (int /*<<< orphan*/ *) ; 
 TYPE_1__* ossl_provider_find (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ossl_provider_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ossl_provider_upref (TYPE_1__*) ; 
 TYPE_1__* provider_new (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ sk_OSSL_PROVIDER_push (int /*<<< orphan*/ ,TYPE_1__*) ; 

OSSL_PROVIDER *ossl_provider_new(OPENSSL_CTX *libctx, const char *name,
                                 OSSL_provider_init_fn *init_function)
{
    struct provider_store_st *store = NULL;
    OSSL_PROVIDER *prov = NULL;

    if ((store = get_provider_store(libctx)) == NULL)
        return NULL;

    if ((prov = ossl_provider_find(libctx, name)) != NULL) { /* refcount +1 */
        ossl_provider_free(prov); /* refcount -1 */
        CRYPTOerr(CRYPTO_F_OSSL_PROVIDER_NEW,
                  CRYPTO_R_PROVIDER_ALREADY_EXISTS);
        ERR_add_error_data(2, "name=", name);
        return NULL;
    }

    /* provider_new() generates an error, so no need here */
    if ((prov = provider_new(name, init_function)) == NULL)
        return NULL;

    CRYPTO_THREAD_write_lock(store->lock);
    if (!ossl_provider_upref(prov)) { /* +1 One reference for the store */
        ossl_provider_free(prov); /* -1 Reference that was to be returned */
        prov = NULL;
    } else if (sk_OSSL_PROVIDER_push(store->providers, prov) == 0) {
        ossl_provider_free(prov); /* -1 Store reference */
        ossl_provider_free(prov); /* -1 Reference that was to be returned */
        prov = NULL;
    } else {
        prov->store = store;
    }
    CRYPTO_THREAD_unlock(store->lock);

    if (prov == NULL)
        CRYPTOerr(CRYPTO_F_OSSL_PROVIDER_NEW, ERR_R_MALLOC_FAILURE);

    /*
     * At this point, the provider is only partially "loaded".  To be
     * fully "loaded", ossl_provider_activate() must also be called.
     */

    return prov;
}