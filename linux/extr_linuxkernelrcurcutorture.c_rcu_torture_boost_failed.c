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
 int HZ ; 
 int /*<<< orphan*/  VERBOSE_TOROUT_STRING (char*) ; 
 int /*<<< orphan*/  n_rcu_torture_boost_failure ; 
 int test_boost_duration ; 

__attribute__((used)) static bool rcu_torture_boost_failed(unsigned long start, unsigned long end)
{
	if (end - start > test_boost_duration * HZ - HZ / 2) {
		VERBOSE_TOROUT_STRING("rcu_torture_boost boosting failed");
		n_rcu_torture_boost_failure++;

		return true; /* failed */
	}

	return false; /* passed */
}