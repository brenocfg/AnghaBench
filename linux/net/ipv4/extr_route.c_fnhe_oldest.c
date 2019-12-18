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
struct fnhe_hash_bucket {int /*<<< orphan*/  chain; } ;
struct fib_nh_exception {int /*<<< orphan*/  fnhe_stamp; int /*<<< orphan*/  fnhe_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  fnhe_flush_routes (struct fib_nh_exception*) ; 
 struct fib_nh_exception* rcu_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fib_nh_exception *fnhe_oldest(struct fnhe_hash_bucket *hash)
{
	struct fib_nh_exception *fnhe, *oldest;

	oldest = rcu_dereference(hash->chain);
	for (fnhe = rcu_dereference(oldest->fnhe_next); fnhe;
	     fnhe = rcu_dereference(fnhe->fnhe_next)) {
		if (time_before(fnhe->fnhe_stamp, oldest->fnhe_stamp))
			oldest = fnhe;
	}
	fnhe_flush_routes(oldest);
	return oldest;
}