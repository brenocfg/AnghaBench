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
struct TYPE_6__ {int /*<<< orphan*/ * global_properties; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ OSSL_METHOD_STORE ;

/* Variables and functions */
 int /*<<< orphan*/  ossl_method_cache_flush_all (TYPE_1__*) ; 
 int /*<<< orphan*/ * ossl_parse_query (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ossl_property_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_property_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ossl_property_write_lock (TYPE_1__*) ; 

int ossl_method_store_set_global_properties(OSSL_METHOD_STORE *store,
                                            const char *prop_query) {
    int ret = 0;

    if (store == NULL)
        return 1;

    ossl_property_write_lock(store);
    ossl_method_cache_flush_all(store);
    if (prop_query == NULL) {
        ossl_property_free(store->global_properties);
        store->global_properties = NULL;
        ossl_property_unlock(store);
        return 1;
    }
    store->global_properties = ossl_parse_query(store->ctx, prop_query);
    ret = store->global_properties != NULL;
    ossl_property_unlock(store);
    return ret;
}