#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union map_priv {int color; int /*<<< orphan*/  ptr; } ;
struct thread {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  color_pids; } ;
struct perf_sched {TYPE_1__ map; } ;
struct machine {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 struct thread* machine__findnew_thread (struct machine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ thread__priv (struct thread*) ; 
 int /*<<< orphan*/  thread__set_priv (struct thread*,int /*<<< orphan*/ ) ; 
 scalar_t__ thread_map__has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct thread*
map__findnew_thread(struct perf_sched *sched, struct machine *machine, pid_t pid, pid_t tid)
{
	struct thread *thread = machine__findnew_thread(machine, pid, tid);
	union map_priv priv = {
		.color = false,
	};

	if (!sched->map.color_pids || !thread || thread__priv(thread))
		return thread;

	if (thread_map__has(sched->map.color_pids, tid))
		priv.color = true;

	thread__set_priv(thread, priv.ptr);
	return thread;
}