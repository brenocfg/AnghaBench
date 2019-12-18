#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  cache; } ;
struct TYPE_7__ {int /*<<< orphan*/  nelem; } ;
typedef  TYPE_1__ OSSL_METHOD_STORE ;
typedef  TYPE_2__ ALGORITHM ;

/* Variables and functions */
 int /*<<< orphan*/  impl_cache_flush_alg (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ lh_QUERY_num_items (int /*<<< orphan*/ ) ; 
 TYPE_2__* ossl_method_store_retrieve (TYPE_1__*,int) ; 

__attribute__((used)) static void ossl_method_cache_flush(OSSL_METHOD_STORE *store, int nid)
{
    ALGORITHM *alg = ossl_method_store_retrieve(store, nid);

    if (alg != NULL) {
        store->nelem -= lh_QUERY_num_items(alg->cache);
        impl_cache_flush_alg(0, alg);
    }
}