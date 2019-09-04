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

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lh_OSSL_STORE_LOADER_free (int /*<<< orphan*/ *) ; 
 scalar_t__ lh_OSSL_STORE_LOADER_num_items (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * loader_register ; 
 int /*<<< orphan*/ * registry_lock ; 

void ossl_store_destroy_loaders_int(void)
{
    assert(lh_OSSL_STORE_LOADER_num_items(loader_register) == 0);
    lh_OSSL_STORE_LOADER_free(loader_register);
    loader_register = NULL;
    CRYPTO_THREAD_lock_free(registry_lock);
    registry_lock = NULL;
}