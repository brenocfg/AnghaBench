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
struct test_parman {int bulk_budget; int bulk_noop; int /*<<< orphan*/  run_budget; } ;

/* Variables and functions */
 int TEST_PARMAN_BULK_MAX_MASK ; 
 int test_parman_rnd_get (struct test_parman*) ; 

__attribute__((used)) static bool test_parman_run_check_budgets(struct test_parman *test_parman)
{
	if (test_parman->run_budget-- == 0)
		return false;
	if (test_parman->bulk_budget-- != 0)
		return true;

	test_parman->bulk_budget = test_parman_rnd_get(test_parman) &
				   TEST_PARMAN_BULK_MAX_MASK;
	test_parman->bulk_noop = test_parman_rnd_get(test_parman) & 1;
	return true;
}