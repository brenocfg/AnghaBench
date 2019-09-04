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
struct perf_tool {int dummy; } ;
struct machine {int dummy; } ;
typedef  int /*<<< orphan*/  perf_event__handler_t ;

/* Variables and functions */
 int perf_event__synthesize_thread_map (struct perf_tool*,struct thread_map*,int /*<<< orphan*/ ,struct machine*,int,unsigned int) ; 
 int perf_event__synthesize_threads (struct perf_tool*,int /*<<< orphan*/ ,struct machine*,int,unsigned int,unsigned int) ; 
 scalar_t__ target__has_cpu (struct target*) ; 
 scalar_t__ target__has_task (struct target*) ; 

int __machine__synthesize_threads(struct machine *machine, struct perf_tool *tool,
				  struct target *target, struct thread_map *threads,
				  perf_event__handler_t process, bool data_mmap,
				  unsigned int proc_map_timeout,
				  unsigned int nr_threads_synthesize)
{
	if (target__has_task(target))
		return perf_event__synthesize_thread_map(tool, threads, process, machine, data_mmap, proc_map_timeout);
	else if (target__has_cpu(target))
		return perf_event__synthesize_threads(tool, process,
						      machine, data_mmap,
						      proc_map_timeout,
						      nr_threads_synthesize);
	/* command specified */
	return 0;
}