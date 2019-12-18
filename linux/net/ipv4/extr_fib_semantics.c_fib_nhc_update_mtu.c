#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct fnhe_hash_bucket {int /*<<< orphan*/  chain; } ;
struct fib_nh_exception {int fnhe_mtu_locked; scalar_t__ fnhe_pmtu; int /*<<< orphan*/  fnhe_next; } ;
struct fib_nh_common {int /*<<< orphan*/  nhc_exceptions; } ;

/* Variables and functions */
 int FNHE_HASH_SIZE ; 
 void* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 

void fib_nhc_update_mtu(struct fib_nh_common *nhc, u32 new, u32 orig)
{
	struct fnhe_hash_bucket *bucket;
	int i;

	bucket = rcu_dereference_protected(nhc->nhc_exceptions, 1);
	if (!bucket)
		return;

	for (i = 0; i < FNHE_HASH_SIZE; i++) {
		struct fib_nh_exception *fnhe;

		for (fnhe = rcu_dereference_protected(bucket[i].chain, 1);
		     fnhe;
		     fnhe = rcu_dereference_protected(fnhe->fnhe_next, 1)) {
			if (fnhe->fnhe_mtu_locked) {
				if (new <= fnhe->fnhe_pmtu) {
					fnhe->fnhe_pmtu = new;
					fnhe->fnhe_mtu_locked = false;
				}
			} else if (new < fnhe->fnhe_pmtu ||
				   orig == fnhe->fnhe_pmtu) {
				fnhe->fnhe_pmtu = new;
			}
		}
	}
}