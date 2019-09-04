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
struct provider_store_st {int /*<<< orphan*/  lock; scalar_t__ use_fallbacks; int /*<<< orphan*/  providers; } ;
struct TYPE_4__ {scalar_t__ flag_fallback; } ;
typedef  TYPE_1__ OSSL_PROVIDER ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_read_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 struct provider_store_st* get_provider_store (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  provider_activate (TYPE_1__*) ; 
 int provider_forall_loaded (struct provider_store_st*,int*,int (*) (OSSL_PROVIDER*,void*),void*) ; 
 int sk_OSSL_PROVIDER_num (int /*<<< orphan*/ ) ; 
 TYPE_1__* sk_OSSL_PROVIDER_value (int /*<<< orphan*/ ,int) ; 

int ossl_provider_forall_loaded(OPENSSL_CTX *ctx,
                                int (*cb)(OSSL_PROVIDER *provider,
                                          void *cbdata),
                                void *cbdata)
{
    int ret = 1;
    int i;
    struct provider_store_st *store = get_provider_store(ctx);

    if (store != NULL) {
        int found_activated = 0;

        CRYPTO_THREAD_read_lock(store->lock);
        ret = provider_forall_loaded(store, &found_activated, cb, cbdata);

        /*
         * If there's nothing activated ever in this store, try to activate
         * all fallbacks.
         */
        if (!found_activated && store->use_fallbacks) {
            int num_provs = sk_OSSL_PROVIDER_num(store->providers);
            int activated_fallback_count = 0;

            for (i = 0; i < num_provs; i++) {
                OSSL_PROVIDER *prov =
                    sk_OSSL_PROVIDER_value(store->providers, i);

                /*
                 * Note that we don't care if the activation succeeds or
                 * not.  If it doesn't succeed, then the next loop will
                 * fail anyway.
                 */
                if (prov->flag_fallback) {
                    activated_fallback_count++;
                    provider_activate(prov);
                }
            }

            if (activated_fallback_count > 0) {
                /*
                 * We assume that all fallbacks have been added to the store
                 * before any fallback is activated.
                 * TODO: We may have to reconsider this, IF we find ourselves
                 * adding fallbacks after any previous fallback has been
                 * activated.
                 */
                store->use_fallbacks = 0;

                /*
                 * Now that we've activated available fallbacks, try a
                 * second sweep
                 */
                ret = provider_forall_loaded(store, NULL, cb, cbdata);
            }
        }
        CRYPTO_THREAD_unlock(store->lock);
    }

    return ret;
}