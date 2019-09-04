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
struct primes {unsigned long last; unsigned long sz; int /*<<< orphan*/  primes; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_LONG ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int GFP_KERNEL ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  bitmap_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ bitmap_size (unsigned long) ; 
 unsigned long clear_multiples (unsigned long,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 unsigned long find_next_bit (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  kfree (struct primes*) ; 
 int /*<<< orphan*/  kfree_rcu (struct primes*,int /*<<< orphan*/ ) ; 
 struct primes* kmalloc (scalar_t__,int) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  primes ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct primes*) ; 
 struct primes* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long round_up (unsigned long,int /*<<< orphan*/ ) ; 
 struct primes const small_primes ; 

__attribute__((used)) static bool expand_to_next_prime(unsigned long x)
{
	const struct primes *p;
	struct primes *new;
	unsigned long sz, y;

	/* Betrand's Postulate (or Chebyshev's theorem) states that if n > 3,
	 * there is always at least one prime p between n and 2n - 2.
	 * Equivalently, if n > 1, then there is always at least one prime p
	 * such that n < p < 2n.
	 *
	 * http://mathworld.wolfram.com/BertrandsPostulate.html
	 * https://en.wikipedia.org/wiki/Bertrand's_postulate
	 */
	sz = 2 * x;
	if (sz < x)
		return false;

	sz = round_up(sz, BITS_PER_LONG);
	new = kmalloc(sizeof(*new) + bitmap_size(sz),
		      GFP_KERNEL | __GFP_NOWARN);
	if (!new)
		return false;

	mutex_lock(&lock);
	p = rcu_dereference_protected(primes, lockdep_is_held(&lock));
	if (x < p->last) {
		kfree(new);
		goto unlock;
	}

	/* Where memory permits, track the primes using the
	 * Sieve of Eratosthenes. The sieve is to remove all multiples of known
	 * primes from the set, what remains in the set is therefore prime.
	 */
	bitmap_fill(new->primes, sz);
	bitmap_copy(new->primes, p->primes, p->sz);
	for (y = 2UL; y < sz; y = find_next_bit(new->primes, sz, y + 1))
		new->last = clear_multiples(y, new->primes, p->sz, sz);
	new->sz = sz;

	BUG_ON(new->last <= x);

	rcu_assign_pointer(primes, new);
	if (p != &small_primes)
		kfree_rcu((struct primes *)p, rcu);

unlock:
	mutex_unlock(&lock);
	return true;
}