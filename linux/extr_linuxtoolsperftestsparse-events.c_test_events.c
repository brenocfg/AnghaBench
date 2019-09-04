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
struct evlist_test {int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int test_event (struct evlist_test*) ; 

__attribute__((used)) static int test_events(struct evlist_test *events, unsigned cnt)
{
	int ret1, ret2 = 0;
	unsigned i;

	for (i = 0; i < cnt; i++) {
		struct evlist_test *e = &events[i];

		pr_debug("running test %d '%s'", e->id, e->name);
		ret1 = test_event(e);
		if (ret1)
			ret2 = ret1;
		pr_debug("\n");
	}

	return ret2;
}