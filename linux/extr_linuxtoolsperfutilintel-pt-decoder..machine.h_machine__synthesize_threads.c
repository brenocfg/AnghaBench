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
struct thread_map {int dummy; } ;
struct target {int dummy; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 int __machine__synthesize_threads (struct machine*,int /*<<< orphan*/ *,struct target*,struct thread_map*,int /*<<< orphan*/ ,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  perf_event__process ; 

__attribute__((used)) static inline
int machine__synthesize_threads(struct machine *machine, struct target *target,
				struct thread_map *threads, bool data_mmap,
				unsigned int proc_map_timeout,
				unsigned int nr_threads_synthesize)
{
	return __machine__synthesize_threads(machine, NULL, target, threads,
					     perf_event__process, data_mmap,
					     proc_map_timeout,
					     nr_threads_synthesize);
}