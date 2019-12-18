#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  impls; } ;
struct TYPE_11__ {void* method; int /*<<< orphan*/  properties; } ;
struct TYPE_10__ {int /*<<< orphan*/ * global_properties; int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  OSSL_PROPERTY_LIST ;
typedef  TYPE_1__ OSSL_METHOD_STORE ;
typedef  TYPE_2__ IMPLEMENTATION ;
typedef  TYPE_3__ ALGORITHM ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_INIT_LOAD_CONFIG ; 
 int /*<<< orphan*/  OPENSSL_init_crypto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* ossl_method_store_retrieve (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * ossl_parse_query (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ossl_property_free (int /*<<< orphan*/ *) ; 
 int ossl_property_has_optional (int /*<<< orphan*/ *) ; 
 int ossl_property_match_count (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ossl_property_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_property_read_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  ossl_property_unlock (TYPE_1__*) ; 
 int sk_IMPLEMENTATION_num (int /*<<< orphan*/ ) ; 
 TYPE_2__* sk_IMPLEMENTATION_value (int /*<<< orphan*/ ,int) ; 

int ossl_method_store_fetch(OSSL_METHOD_STORE *store, int nid,
                            const char *prop_query, void **method)
{
    ALGORITHM *alg;
    IMPLEMENTATION *impl;
    OSSL_PROPERTY_LIST *pq = NULL, *p2;
    int ret = 0;
    int j, best = -1, score, optional;

#ifndef FIPS_MODE
    OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CONFIG, NULL);
#endif

    if (nid <= 0 || method == NULL || store == NULL)
        return 0;

    /*
     * This only needs to be a read lock, because queries never create property
     * names or value and thus don't modify any of the property string layer.
     */
    ossl_property_read_lock(store);
    alg = ossl_method_store_retrieve(store, nid);
    if (alg == NULL) {
        ossl_property_unlock(store);
        return 0;
    }

    if (prop_query == NULL) {
        if ((impl = sk_IMPLEMENTATION_value(alg->impls, 0)) != NULL) {
            *method = impl->method;
            ret = 1;
        }
        goto fin;
    }
    pq = ossl_parse_query(store->ctx, prop_query);
    if (pq == NULL)
        goto fin;
    if (store->global_properties != NULL) {
        p2 = ossl_property_merge(pq, store->global_properties);
        if (p2 == NULL)
            goto fin;
        ossl_property_free(pq);
        pq = p2;
    }
    optional = ossl_property_has_optional(pq);
    for (j = 0; j < sk_IMPLEMENTATION_num(alg->impls); j++) {
        impl = sk_IMPLEMENTATION_value(alg->impls, j);
        score = ossl_property_match_count(pq, impl->properties);
        if (score > best) {
            *method = impl->method;
            ret = 1;
            if (!optional)
                goto fin;
            best = score;
        }
    }
fin:
    ossl_property_unlock(store);
    ossl_property_free(pq);
    return ret;
}