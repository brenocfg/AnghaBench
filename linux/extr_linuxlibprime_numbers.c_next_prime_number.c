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
struct primes {unsigned long last; int /*<<< orphan*/  primes; } ;

/* Variables and functions */
 int /*<<< orphan*/  expand_to_next_prime (unsigned long) ; 
 unsigned long find_next_bit (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  primes ; 
 struct primes* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 unsigned long slow_next_prime_number (unsigned long) ; 

unsigned long next_prime_number(unsigned long x)
{
	const struct primes *p;

	rcu_read_lock();
	p = rcu_dereference(primes);
	while (x >= p->last) {
		rcu_read_unlock();

		if (!expand_to_next_prime(x))
			return slow_next_prime_number(x);

		rcu_read_lock();
		p = rcu_dereference(primes);
	}
	x = find_next_bit(p->primes, p->last, x + 1);
	rcu_read_unlock();

	return x;
}