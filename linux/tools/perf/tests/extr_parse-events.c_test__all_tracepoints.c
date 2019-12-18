#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ nr_entries; } ;
struct evlist {TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 scalar_t__ count_tracepoints () ; 
 int test__checkevent_tracepoint_multi (struct evlist*) ; 

__attribute__((used)) static int test__all_tracepoints(struct evlist *evlist)
{
	TEST_ASSERT_VAL("wrong events count",
			count_tracepoints() == evlist->core.nr_entries);

	return test__checkevent_tracepoint_multi(evlist);
}