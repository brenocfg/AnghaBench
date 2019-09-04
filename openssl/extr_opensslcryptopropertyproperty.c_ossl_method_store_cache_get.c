#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  cache; } ;
struct TYPE_6__ {char const* query; void* method; } ;
typedef  TYPE_1__ QUERY ;
typedef  int /*<<< orphan*/  OSSL_METHOD_STORE ;
typedef  TYPE_2__ ALGORITHM ;

/* Variables and functions */
 TYPE_1__* lh_QUERY_retrieve (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__* ossl_method_store_retrieve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ossl_property_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_property_unlock (int /*<<< orphan*/ *) ; 

int ossl_method_store_cache_get(OSSL_METHOD_STORE *store, int nid,
                                const char *prop_query, void **method)
{
    ALGORITHM *alg;
    QUERY elem, *r;

    if (nid <= 0 || store == NULL)
        return 0;

    ossl_property_read_lock(store);
    alg = ossl_method_store_retrieve(store, nid);
    if (alg == NULL) {
        ossl_property_unlock(store);
        return 0;
    }

    elem.query = prop_query != NULL ? prop_query : "";
    r = lh_QUERY_retrieve(alg->cache, &elem);
    if (r == NULL) {
        ossl_property_unlock(store);
        return 0;
    }
    *method = r->method;
    ossl_property_unlock(store);
    return 1;
}