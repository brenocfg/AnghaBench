#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nelem; int /*<<< orphan*/  algs; } ;
typedef  TYPE_1__ OSSL_METHOD_STORE ;

/* Variables and functions */
 int /*<<< orphan*/  impl_cache_flush_alg ; 
 int /*<<< orphan*/  ossl_sa_ALGORITHM_doall (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ossl_method_cache_flush_all(OSSL_METHOD_STORE *store)
{
    ossl_sa_ALGORITHM_doall(store->algs, &impl_cache_flush_alg);
    store->nelem = 0;
}