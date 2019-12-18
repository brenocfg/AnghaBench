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
struct TYPE_3__ {int exclude_guest; int /*<<< orphan*/  exclude_host; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;
struct evlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 struct evsel* evlist__first (struct evlist*) ; 
 int test__checkevent_symbolic_name (struct evlist*) ; 

__attribute__((used)) static int test__checkevent_exclude_guest_modifier(struct evlist *evlist)
{
	struct evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong exclude guest", evsel->core.attr.exclude_guest);
	TEST_ASSERT_VAL("wrong exclude host", !evsel->core.attr.exclude_host);

	return test__checkevent_symbolic_name(evlist);
}