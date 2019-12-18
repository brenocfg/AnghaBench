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
struct evsel {int dummy; } ;

/* Variables and functions */
 int __perf_evsel__read_on_cpu (struct evsel*,int,int,int) ; 

__attribute__((used)) static inline int perf_evsel__read_on_cpu_scaled(struct evsel *evsel,
						 int cpu, int thread)
{
	return __perf_evsel__read_on_cpu(evsel, cpu, thread, true);
}