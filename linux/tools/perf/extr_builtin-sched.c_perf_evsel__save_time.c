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
typedef  void* u64 ;
typedef  int u32 ;
struct evsel_runtime {int ncpu; void** last_time; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 int __roundup_pow_of_two (int) ; 
 struct evsel_runtime* perf_evsel__get_runtime (struct evsel*) ; 
 void* realloc (void**,int) ; 

__attribute__((used)) static void perf_evsel__save_time(struct evsel *evsel,
				  u64 timestamp, u32 cpu)
{
	struct evsel_runtime *r = perf_evsel__get_runtime(evsel);

	if (r == NULL)
		return;

	if ((cpu >= r->ncpu) || (r->last_time == NULL)) {
		int i, n = __roundup_pow_of_two(cpu+1);
		void *p = r->last_time;

		p = realloc(r->last_time, n * sizeof(u64));
		if (!p)
			return;

		r->last_time = p;
		for (i = r->ncpu; i < n; ++i)
			r->last_time[i] = (u64) 0;

		r->ncpu = n;
	}

	r->last_time[cpu] = timestamp;
}