#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct total_run_stats {TYPE_1__* sched; int /*<<< orphan*/  total_run_time; int /*<<< orphan*/  sched_count; int /*<<< orphan*/  task_count; } ;
struct TYPE_4__ {scalar_t__ n; } ;
struct thread_runtime {scalar_t__ total_run_time; TYPE_2__ run_stats; } ;
struct thread {int dummy; } ;
struct TYPE_3__ {scalar_t__ show_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  print_thread_runtime (struct thread*,struct thread_runtime*) ; 
 int /*<<< orphan*/  print_thread_waittime (struct thread*,struct thread_runtime*) ; 
 scalar_t__ thread__is_filtered (struct thread*) ; 
 struct thread_runtime* thread__priv (struct thread*) ; 

__attribute__((used)) static int __show_thread_runtime(struct thread *t, void *priv)
{
	struct total_run_stats *stats = priv;
	struct thread_runtime *r;

	if (thread__is_filtered(t))
		return 0;

	r = thread__priv(t);
	if (r && r->run_stats.n) {
		stats->task_count++;
		stats->sched_count += r->run_stats.n;
		stats->total_run_time += r->total_run_time;

		if (stats->sched->show_state)
			print_thread_waittime(t, r);
		else
			print_thread_runtime(t, r);
	}

	return 0;
}