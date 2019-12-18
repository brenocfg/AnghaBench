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
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int flag_initialized; TYPE_2__* store; } ;
typedef  TYPE_1__ OSSL_PROVIDER ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_read_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  provider_activate_fallbacks (TYPE_2__*) ; 

int ossl_provider_available(OSSL_PROVIDER *prov)
{
    if (prov != NULL) {
        CRYPTO_THREAD_read_lock(prov->store->lock);
        provider_activate_fallbacks(prov->store);
        CRYPTO_THREAD_unlock(prov->store->lock);

        return prov->flag_initialized;
    }
    return 0;
}