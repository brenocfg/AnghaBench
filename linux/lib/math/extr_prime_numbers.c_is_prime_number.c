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
struct primes {unsigned long sz; int /*<<< orphan*/  primes; } ;

/* Variables and functions */
 int /*<<< orphan*/  expand_to_next_prime (unsigned long) ; 
 int /*<<< orphan*/  primes ; 
 struct primes* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int slow_is_prime_number (unsigned long) ; 
 int test_bit (unsigned long,int /*<<< orphan*/ ) ; 

bool is_prime_number(unsigned long x)
{
	const struct primes *p;
	bool result;

	rcu_read_lock();
	p = rcu_dereference(primes);
	while (x >= p->sz) {
		rcu_read_unlock();

		if (!expand_to_next_prime(x))
			return slow_is_prime_number(x);

		rcu_read_lock();
		p = rcu_dereference(primes);
	}
	result = test_bit(x, p->primes);
	rcu_read_unlock();

	return result;
}