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
struct perf_cpu_map {unsigned int nr; int /*<<< orphan*/ * map; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 unsigned int nthreads ; 
 scalar_t__ pthread_attr_setaffinity_np (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int threads_starting ; 
 int /*<<< orphan*/  workerfn ; 

__attribute__((used)) static void block_threads(pthread_t *w,
			  pthread_attr_t thread_attr, struct perf_cpu_map *cpu)
{
	cpu_set_t cpuset;
	unsigned int i;

	threads_starting = nthreads;

	/* create and block all threads */
	for (i = 0; i < nthreads; i++) {
		CPU_ZERO(&cpuset);
		CPU_SET(cpu->map[i % cpu->nr], &cpuset);

		if (pthread_attr_setaffinity_np(&thread_attr, sizeof(cpu_set_t), &cpuset))
			err(EXIT_FAILURE, "pthread_attr_setaffinity_np");

		if (pthread_create(&w[i], &thread_attr, workerfn, NULL))
			err(EXIT_FAILURE, "pthread_create");
	}
}