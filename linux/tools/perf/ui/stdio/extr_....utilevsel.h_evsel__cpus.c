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
struct perf_cpu_map {int dummy; } ;
struct evsel {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 struct perf_cpu_map* perf_evsel__cpus (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct perf_cpu_map *evsel__cpus(struct evsel *evsel)
{
	return perf_evsel__cpus(&evsel->core);
}