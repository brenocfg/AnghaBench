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
struct provider_store_st {int /*<<< orphan*/  lock; int /*<<< orphan*/  providers; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (struct provider_store_st*) ; 
 int /*<<< orphan*/  ossl_provider_free ; 
 int /*<<< orphan*/  sk_OSSL_PROVIDER_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void provider_store_free(void *vstore)
{
    struct provider_store_st *store = vstore;

    if (store == NULL)
        return;
    sk_OSSL_PROVIDER_pop_free(store->providers, ossl_provider_free);
    CRYPTO_THREAD_lock_free(store->lock);
    OPENSSL_free(store);
}