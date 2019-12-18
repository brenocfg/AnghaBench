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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  tstr ;
struct thread {int dummy; } ;
struct perf_sched {scalar_t__ max_cpu; scalar_t__ show_cpu_visual; scalar_t__ summary_only; } ;
struct perf_sample {int cpu; int /*<<< orphan*/  time; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
struct machine {int dummy; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 char* comm_width ; 
 struct thread* machine__findnew_thread (struct machine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_evsel__intval (struct evsel*,struct perf_sample*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* timehist_get_commstr (struct thread*) ; 
 scalar_t__ timehist_skip_sample (struct perf_sched*,struct thread*,struct evsel*,struct perf_sample*) ; 
 int /*<<< orphan*/  timestamp__scnprintf_usec (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void timehist_print_migration_event(struct perf_sched *sched,
					struct evsel *evsel,
					struct perf_sample *sample,
					struct machine *machine,
					struct thread *migrated)
{
	struct thread *thread;
	char tstr[64];
	u32 max_cpus = sched->max_cpu + 1;
	u32 ocpu, dcpu;

	if (sched->summary_only)
		return;

	max_cpus = sched->max_cpu + 1;
	ocpu = perf_evsel__intval(evsel, sample, "orig_cpu");
	dcpu = perf_evsel__intval(evsel, sample, "dest_cpu");

	thread = machine__findnew_thread(machine, sample->pid, sample->tid);
	if (thread == NULL)
		return;

	if (timehist_skip_sample(sched, thread, evsel, sample) &&
	    timehist_skip_sample(sched, migrated, evsel, sample)) {
		return;
	}

	timestamp__scnprintf_usec(sample->time, tstr, sizeof(tstr));
	printf("%15s [%04d] ", tstr, sample->cpu);

	if (sched->show_cpu_visual) {
		u32 i;
		char c;

		printf("  ");
		for (i = 0; i < max_cpus; ++i) {
			c = (i == sample->cpu) ? 'm' : ' ';
			printf("%c", c);
		}
		printf("  ");
	}

	printf(" %-*s ", comm_width, timehist_get_commstr(thread));

	/* dt spacer */
	printf("  %9s  %9s  %9s ", "", "", "");

	printf("migrated: %s", timehist_get_commstr(migrated));
	printf(" cpu %d => %d", ocpu, dcpu);

	printf("\n");
}