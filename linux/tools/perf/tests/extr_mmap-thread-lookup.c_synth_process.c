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
struct perf_thread_map {int dummy; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  perf_event__process ; 
 int perf_event__synthesize_thread_map (int /*<<< orphan*/ *,struct perf_thread_map*,int /*<<< orphan*/ ,struct machine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_thread_map__put (struct perf_thread_map*) ; 
 struct perf_thread_map* thread_map__new_by_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int synth_process(struct machine *machine)
{
	struct perf_thread_map *map;
	int err;

	map = thread_map__new_by_pid(getpid());

	err = perf_event__synthesize_thread_map(NULL, map,
						perf_event__process,
						machine, 0);

	perf_thread_map__put(map);
	return err;
}