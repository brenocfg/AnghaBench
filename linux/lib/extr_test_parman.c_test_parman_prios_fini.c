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
struct test_parman_prio {int /*<<< orphan*/  parman_prio; } ;
struct test_parman {struct test_parman_prio* prios; } ;

/* Variables and functions */
 int TEST_PARMAN_PRIO_COUNT ; 
 int /*<<< orphan*/  parman_prio_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_parman_prios_fini(struct test_parman *test_parman)
{
	int i;

	for (i = 0; i < TEST_PARMAN_PRIO_COUNT; i++) {
		struct test_parman_prio *prio = &test_parman->prios[i];

		parman_prio_fini(&prio->parman_prio);
	}
}