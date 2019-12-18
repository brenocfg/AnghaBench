#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ossl_uintmax_t ;
struct TYPE_6__ {int /*<<< orphan*/  cache; } ;
struct TYPE_5__ {int /*<<< orphan*/  cache; } ;
typedef  TYPE_1__ IMPL_CACHE_FLUSH ;
typedef  TYPE_2__ ALGORITHM ;

/* Variables and functions */
 int /*<<< orphan*/  impl_cache_flush_cache ; 
 int /*<<< orphan*/  lh_QUERY_doall_IMPL_CACHE_FLUSH (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void impl_cache_flush_one_alg(ossl_uintmax_t idx, ALGORITHM *alg,
                                     void *v)
{
    IMPL_CACHE_FLUSH *state = (IMPL_CACHE_FLUSH *)v;

    state->cache = alg->cache;
    lh_QUERY_doall_IMPL_CACHE_FLUSH(state->cache, &impl_cache_flush_cache,
                                    state);
}