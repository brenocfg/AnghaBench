#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int nid; int /*<<< orphan*/ * impls; int /*<<< orphan*/ * cache; } ;
struct TYPE_20__ {void (* method_destruct ) (void*) ;scalar_t__ properties; int /*<<< orphan*/  const* provider; void* method; } ;
struct TYPE_19__ {int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;
typedef  TYPE_1__ OSSL_METHOD_STORE ;
typedef  TYPE_2__ IMPLEMENTATION ;
typedef  TYPE_3__ ALGORITHM ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_2__*) ; 
 TYPE_2__* OPENSSL_malloc (int) ; 
 TYPE_3__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  alg_cleanup (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  impl_free (TYPE_2__*) ; 
 int /*<<< orphan*/ * lh_QUERY_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_method_cache_flush (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ossl_method_store_insert (TYPE_1__*,TYPE_3__*) ; 
 TYPE_3__* ossl_method_store_retrieve (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * ossl_parse_property (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * ossl_prop_defn_get (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ossl_prop_defn_set (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_property_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ossl_property_write_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  query_cmp ; 
 int /*<<< orphan*/  query_hash ; 
 int /*<<< orphan*/ * sk_IMPLEMENTATION_new_null () ; 
 int sk_IMPLEMENTATION_num (int /*<<< orphan*/ *) ; 
 scalar_t__ sk_IMPLEMENTATION_push (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* sk_IMPLEMENTATION_value (int /*<<< orphan*/ *,int) ; 

int ossl_method_store_add(OSSL_METHOD_STORE *store, const OSSL_PROVIDER *prov,
                          int nid, const char *properties, void *method,
                          int (*method_up_ref)(void *),
                          void (*method_destruct)(void *))
{
    ALGORITHM *alg = NULL;
    IMPLEMENTATION *impl;
    int ret = 0;
    int i;

    if (nid <= 0 || method == NULL || store == NULL)
        return 0;
    if (properties == NULL)
        properties = "";

    /* Create new entry */
    impl = OPENSSL_malloc(sizeof(*impl));
    if (impl == NULL)
        return 0;
    if (method_up_ref != NULL && !method_up_ref(method)) {
        OPENSSL_free(impl);
        return 0;
    }
    impl->provider = prov;
    impl->method = method;
    impl->method_destruct = method_destruct;

    /*
     * Insert into the hash table if required.
     *
     * A write lock is used unconditionally because we wend our way down to the
     * property string code which isn't locking friendly.
     */
    ossl_property_write_lock(store);
    ossl_method_cache_flush(store, nid);
    if ((impl->properties = ossl_prop_defn_get(store->ctx, properties)) == NULL) {
        impl->properties = ossl_parse_property(store->ctx, properties);
        if (impl->properties == NULL)
            goto err;
        ossl_prop_defn_set(store->ctx, properties, impl->properties);
    }

    alg = ossl_method_store_retrieve(store, nid);
    if (alg == NULL) {
        if ((alg = OPENSSL_zalloc(sizeof(*alg))) == NULL
                || (alg->impls = sk_IMPLEMENTATION_new_null()) == NULL
                || (alg->cache = lh_QUERY_new(&query_hash, &query_cmp)) == NULL)
            goto err;
        alg->nid = nid;
        if (!ossl_method_store_insert(store, alg))
            goto err;
    }

    /* Push onto stack if there isn't one there already */
    for (i = 0; i < sk_IMPLEMENTATION_num(alg->impls); i++) {
        const IMPLEMENTATION *tmpimpl = sk_IMPLEMENTATION_value(alg->impls, i);

        if (tmpimpl->provider == impl->provider
            && tmpimpl->properties == impl->properties)
            break;
    }
    if (i == sk_IMPLEMENTATION_num(alg->impls)
        && sk_IMPLEMENTATION_push(alg->impls, impl))
        ret = 1;
    ossl_property_unlock(store);
    if (ret == 0)
        impl_free(impl);
    return ret;

err:
    ossl_property_unlock(store);
    alg_cleanup(0, alg);
    impl_free(impl);
    return 0;
}