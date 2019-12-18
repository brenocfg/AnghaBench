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
struct rt6_exception_bucket {int dummy; } ;
struct fib6_nh {int /*<<< orphan*/  rt6i_exception_bucket; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 unsigned long FIB6_EXCEPTION_BUCKET_FLUSHED ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct rt6_exception_bucket*) ; 
 struct rt6_exception_bucket* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fib6_nh_excptn_bucket_set_flushed(struct fib6_nh *nh,
					      spinlock_t *lock)
{
	struct rt6_exception_bucket *bucket;
	unsigned long p;

	bucket = rcu_dereference_protected(nh->rt6i_exception_bucket,
					   lockdep_is_held(lock));

	p = (unsigned long)bucket;
	p |= FIB6_EXCEPTION_BUCKET_FLUSHED;
	bucket = (struct rt6_exception_bucket *)p;
	rcu_assign_pointer(nh->rt6i_exception_bucket, bucket);
}