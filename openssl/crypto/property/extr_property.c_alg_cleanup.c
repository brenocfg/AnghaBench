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
typedef  int /*<<< orphan*/  ossl_uintmax_t ;
struct TYPE_4__ {int /*<<< orphan*/  cache; int /*<<< orphan*/  impls; } ;
typedef  TYPE_1__ ALGORITHM ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  impl_cache_free ; 
 int /*<<< orphan*/  impl_free ; 
 int /*<<< orphan*/  lh_QUERY_doall (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lh_QUERY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_IMPLEMENTATION_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void alg_cleanup(ossl_uintmax_t idx, ALGORITHM *a)
{
    if (a != NULL) {
        sk_IMPLEMENTATION_pop_free(a->impls, &impl_free);
        lh_QUERY_doall(a->cache, &impl_cache_free);
        lh_QUERY_free(a->cache);
        OPENSSL_free(a);
    }
}