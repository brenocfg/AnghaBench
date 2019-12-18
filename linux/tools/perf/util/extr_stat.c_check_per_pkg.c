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
struct perf_counts_values {scalar_t__ ena; scalar_t__ run; } ;
struct evsel {unsigned long* per_pkg_mask; int /*<<< orphan*/  per_pkg; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  cpu__max_cpu () ; 
 int cpu_map__get_socket (struct perf_cpu_map*,int,int /*<<< orphan*/ *) ; 
 struct perf_cpu_map* evsel__cpus (struct evsel*) ; 
 scalar_t__ perf_cpu_map__empty (struct perf_cpu_map*) ; 
 int test_and_set_bit (int,unsigned long*) ; 
 unsigned long* zalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_per_pkg(struct evsel *counter,
			 struct perf_counts_values *vals, int cpu, bool *skip)
{
	unsigned long *mask = counter->per_pkg_mask;
	struct perf_cpu_map *cpus = evsel__cpus(counter);
	int s;

	*skip = false;

	if (!counter->per_pkg)
		return 0;

	if (perf_cpu_map__empty(cpus))
		return 0;

	if (!mask) {
		mask = zalloc(cpu__max_cpu());
		if (!mask)
			return -ENOMEM;

		counter->per_pkg_mask = mask;
	}

	/*
	 * we do not consider an event that has not run as a good
	 * instance to mark a package as used (skip=1). Otherwise
	 * we may run into a situation where the first CPU in a package
	 * is not running anything, yet the second is, and this function
	 * would mark the package as used after the first CPU and would
	 * not read the values from the second CPU.
	 */
	if (!(vals->run && vals->ena))
		return 0;

	s = cpu_map__get_socket(cpus, cpu, NULL);
	if (s < 0)
		return -1;

	*skip = test_and_set_bit(s, mask) == 1;
	return 0;
}