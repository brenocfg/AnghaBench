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
struct TYPE_7__ {int /*<<< orphan*/  impls; } ;
struct TYPE_6__ {void const* method; } ;
typedef  int /*<<< orphan*/  OSSL_METHOD_STORE ;
typedef  TYPE_1__ IMPLEMENTATION ;
typedef  TYPE_2__ ALGORITHM ;

/* Variables and functions */
 int /*<<< orphan*/  impl_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ossl_method_cache_flush (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* ossl_method_store_retrieve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ossl_property_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_property_write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_IMPLEMENTATION_delete (int /*<<< orphan*/ ,int) ; 
 int sk_IMPLEMENTATION_num (int /*<<< orphan*/ ) ; 
 TYPE_1__* sk_IMPLEMENTATION_value (int /*<<< orphan*/ ,int) ; 

int ossl_method_store_remove(OSSL_METHOD_STORE *store, int nid,
                             const void *method)
{
    ALGORITHM *alg = NULL;
    int i;

    if (nid <= 0 || method == NULL || store == NULL)
        return 0;

    ossl_property_write_lock(store);
    ossl_method_cache_flush(store, nid);
    alg = ossl_method_store_retrieve(store, nid);
    if (alg == NULL) {
        ossl_property_unlock(store);
        return 0;
    }

    /*
     * A sorting find then a delete could be faster but these stacks should be
     * relatively small, so we avoid the overhead.  Sorting could also surprise
     * users when result orderings change (even though they are not guaranteed).
     */
    for (i = 0; i < sk_IMPLEMENTATION_num(alg->impls); i++) {
        IMPLEMENTATION *impl = sk_IMPLEMENTATION_value(alg->impls, i);

        if (impl->method == method) {
            sk_IMPLEMENTATION_delete(alg->impls, i);
            ossl_property_unlock(store);
            impl_free(impl);
            return 1;
        }
    }
    ossl_property_unlock(store);
    return 0;
}