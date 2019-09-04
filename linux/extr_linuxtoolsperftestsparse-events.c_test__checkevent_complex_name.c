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
struct perf_evsel {int /*<<< orphan*/  name; } ;
struct perf_evlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_VAL (char*,int) ; 
 struct perf_evsel* perf_evlist__first (struct perf_evlist*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int test__checkevent_complex_name(struct perf_evlist *evlist)
{
	struct perf_evsel *evsel = perf_evlist__first(evlist);

	TEST_ASSERT_VAL("wrong complex name parsing", strcmp(evsel->name, "COMPLEX_CYCLES_NAME:orig=cycles,desc=chip-clock-ticks") == 0);
	return 0;
}