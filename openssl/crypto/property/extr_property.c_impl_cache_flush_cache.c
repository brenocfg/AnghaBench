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
typedef  int uint32_t ;
struct TYPE_3__ {int seed; int /*<<< orphan*/  nelem; int /*<<< orphan*/  cache; } ;
typedef  int /*<<< orphan*/  QUERY ;
typedef  TYPE_1__ IMPL_CACHE_FLUSH ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lh_QUERY_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void impl_cache_flush_cache(QUERY *c, IMPL_CACHE_FLUSH *state)
{
    uint32_t n;

    /*
     * Implement the 32 bit xorshift as suggested by George Marsaglia in:
     *      https://doi.org/10.18637/jss.v008.i14
     *
     * This is a very fast PRNG so there is no need to extract bits one at a
     * time and use the entire value each time.
     */
    n = state->seed;
    n ^= n << 13;
    n ^= n >> 17;
    n ^= n << 5;
    state->seed = n;

    if ((n & 1) != 0)
        OPENSSL_free(lh_QUERY_delete(state->cache, c));
    else
        state->nelem++;
}