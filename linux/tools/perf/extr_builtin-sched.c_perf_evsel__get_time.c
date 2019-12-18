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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct evsel_runtime {size_t ncpu; int /*<<< orphan*/ * last_time; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 struct evsel_runtime* perf_evsel__get_runtime (struct evsel*) ; 

__attribute__((used)) static u64 perf_evsel__get_time(struct evsel *evsel, u32 cpu)
{
	struct evsel_runtime *r = perf_evsel__get_runtime(evsel);

	if ((r == NULL) || (r->last_time == NULL) || (cpu >= r->ncpu))
		return 0;

	return r->last_time[cpu];
}