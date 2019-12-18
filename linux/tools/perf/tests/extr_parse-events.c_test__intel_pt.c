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
struct evsel {int /*<<< orphan*/  name; } ;
struct evlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 struct evsel* evlist__first (struct evlist*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int test__intel_pt(struct evlist *evlist)
{
	struct evsel *evsel = evlist__first(evlist);

	TEST_ASSERT_VAL("wrong name setting", strcmp(evsel->name, "intel_pt//u") == 0);
	return 0;
}