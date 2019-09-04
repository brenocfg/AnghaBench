#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  nelem; int /*<<< orphan*/  cache; TYPE_1__* store; } ;
struct TYPE_4__ {int nbits; int* rand_bits; } ;
typedef  int /*<<< orphan*/  QUERY ;
typedef  TYPE_1__ OSSL_METHOD_STORE ;
typedef  TYPE_2__ IMPL_CACHE_FLUSH ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAND_bytes (int*,int) ; 
 int /*<<< orphan*/  lh_QUERY_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void impl_cache_flush_cache(QUERY *c, IMPL_CACHE_FLUSH *state)
{
    OSSL_METHOD_STORE *store = state->store;
    unsigned int n;

    if (store->nbits == 0) {
        if (!RAND_bytes(store->rand_bits, sizeof(store->rand_bits)))
            return;
        store->nbits = sizeof(store->rand_bits) * 8;
    }
    n = --store->nbits;
    if ((store->rand_bits[n >> 3] & (1 << (n & 7))) != 0)
        OPENSSL_free(lh_QUERY_delete(state->cache, c));
    else
        state->nelem++;
}