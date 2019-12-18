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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dump_primes () ; 
 int is_prime_number (unsigned long) ; 
 unsigned long next_prime_number (unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,...) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long,unsigned long) ; 
 int slow_is_prime_number (unsigned long) ; 

__attribute__((used)) static int selftest(unsigned long max)
{
	unsigned long x, last;

	if (!max)
		return 0;

	for (last = 0, x = 2; x < max; x++) {
		bool slow = slow_is_prime_number(x);
		bool fast = is_prime_number(x);

		if (slow != fast) {
			pr_err("inconsistent result for is-prime(%lu): slow=%s, fast=%s!",
			       x, slow ? "yes" : "no", fast ? "yes" : "no");
			goto err;
		}

		if (!slow)
			continue;

		if (next_prime_number(last) != x) {
			pr_err("incorrect result for next-prime(%lu): expected %lu, got %lu",
			       last, x, next_prime_number(last));
			goto err;
		}
		last = x;
	}

	pr_info("selftest(%lu) passed, last prime was %lu", x, last);
	return 0;

err:
	dump_primes();
	return -EINVAL;
}