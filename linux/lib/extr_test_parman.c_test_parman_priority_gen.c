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
struct test_parman_prio {unsigned long priority; } ;
struct test_parman {struct test_parman_prio* prios; } ;

/* Variables and functions */
 int TEST_PARMAN_PRIO_COUNT ; 
 unsigned long test_parman_rnd_get (struct test_parman*) ; 

__attribute__((used)) static unsigned long test_parman_priority_gen(struct test_parman *test_parman)
{
	unsigned long priority;
	int i;

again:
	priority = test_parman_rnd_get(test_parman);
	if (priority == 0)
		goto again;

	for (i = 0; i < TEST_PARMAN_PRIO_COUNT; i++) {
		struct test_parman_prio *prio = &test_parman->prios[i];

		if (prio->priority == 0)
			break;
		if (prio->priority == priority)
			goto again;
	}
	return priority;
}