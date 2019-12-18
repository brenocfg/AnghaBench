#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int exclude_user; int exclude_kernel; int precise_ip; int /*<<< orphan*/  exclude_hv; } ;
struct TYPE_3__ {TYPE_2__ attr; } ;
struct evsel {TYPE_1__ core; } ;
struct evlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 struct evsel* evlist__first (struct evlist*) ; 
 int /*<<< orphan*/  perf_evsel__name (struct evsel*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int test__checkevent_breakpoint_r (struct evlist*) ; 

__attribute__((used)) static int test__checkevent_breakpoint_r_modifier(struct evlist *evlist)
{
	struct evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude_user", evsel->core.attr.exclude_user);
	TEST_ASSERT_VAL("wrong exclude_kernel", evsel->core.attr.exclude_kernel);
	TEST_ASSERT_VAL("wrong exclude_hv", !evsel->core.attr.exclude_hv);
	TEST_ASSERT_VAL("wrong precise_ip", evsel->core.attr.precise_ip);
	TEST_ASSERT_VAL("wrong name",
			!strcmp(perf_evsel__name(evsel), "mem:0:r:hp"));

	return test__checkevent_breakpoint_r(evlist);
}