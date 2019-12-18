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
struct thread {int dummy; } ;
struct perf_sched {scalar_t__ idle_hist; } ;
struct perf_sample {int /*<<< orphan*/  cpu; scalar_t__ tid; int /*<<< orphan*/  pid; } ;
struct machine {int dummy; } ;
struct idle_thread_runtime {struct thread* last_thread; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 struct thread* get_idle_thread (int /*<<< orphan*/ ) ; 
 scalar_t__ is_idle_sample (struct perf_sample*,struct evsel*) ; 
 struct thread* machine__findnew_thread (struct machine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_evsel__intval (struct evsel*,struct perf_sample*,char*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_idle_callchain (struct perf_sched*,struct idle_thread_runtime*,struct perf_sample*) ; 
 int /*<<< orphan*/  save_task_callchain (struct perf_sched*,struct perf_sample*,struct evsel*,struct machine*) ; 
 struct idle_thread_runtime* thread__priv (struct thread*) ; 

__attribute__((used)) static struct thread *timehist_get_thread(struct perf_sched *sched,
					  struct perf_sample *sample,
					  struct machine *machine,
					  struct evsel *evsel)
{
	struct thread *thread;

	if (is_idle_sample(sample, evsel)) {
		thread = get_idle_thread(sample->cpu);
		if (thread == NULL)
			pr_err("Failed to get idle thread for cpu %d.\n", sample->cpu);

	} else {
		/* there were samples with tid 0 but non-zero pid */
		thread = machine__findnew_thread(machine, sample->pid,
						 sample->tid ?: sample->pid);
		if (thread == NULL) {
			pr_debug("Failed to get thread for tid %d. skipping sample.\n",
				 sample->tid);
		}

		save_task_callchain(sched, sample, evsel, machine);
		if (sched->idle_hist) {
			struct thread *idle;
			struct idle_thread_runtime *itr;

			idle = get_idle_thread(sample->cpu);
			if (idle == NULL) {
				pr_err("Failed to get idle thread for cpu %d.\n", sample->cpu);
				return NULL;
			}

			itr = thread__priv(idle);
			if (itr == NULL)
				return NULL;

			itr->last_thread = thread;

			/* copy task callchain when entering to idle */
			if (perf_evsel__intval(evsel, sample, "next_pid") == 0)
				save_idle_callchain(sched, itr, sample);
		}
	}

	return thread;
}