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
struct primes {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct primes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  primes ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct primes const*) ; 
 struct primes* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct primes const small_primes ; 

__attribute__((used)) static void free_primes(void)
{
	const struct primes *p;

	mutex_lock(&lock);
	p = rcu_dereference_protected(primes, lockdep_is_held(&lock));
	if (p != &small_primes) {
		rcu_assign_pointer(primes, &small_primes);
		kfree_rcu((struct primes *)p, rcu);
	}
	mutex_unlock(&lock);
}