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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  tstr ;
struct thread_runtime {scalar_t__ dt_run; scalar_t__ dt_delay; scalar_t__ dt_preempt; scalar_t__ dt_iowait; scalar_t__ dt_sleep; } ;
struct thread {scalar_t__ tid; } ;
struct perf_sched {scalar_t__ max_cpu; scalar_t__ show_callchain; scalar_t__ show_next; scalar_t__ show_wakeups; scalar_t__ show_state; scalar_t__ show_cpu_visual; } ;
struct perf_sample {int cpu; } ;
struct evsel {int dummy; } ;
struct addr_location {int dummy; } ;
typedef  int /*<<< orphan*/  nstr ;
struct TYPE_2__ {int /*<<< orphan*/  bt_stop_list; } ;

/* Variables and functions */
 int EVSEL__PRINT_CALLCHAIN_ARROW ; 
 int EVSEL__PRINT_ONELINE ; 
 int EVSEL__PRINT_SKIP_IGNORED ; 
 int EVSEL__PRINT_SYM ; 
 int /*<<< orphan*/  callchain_cursor ; 
 char* comm_width ; 
 scalar_t__ perf_evsel__intval (struct evsel*,struct perf_sample*,char*) ; 
 char* perf_evsel__strval (struct evsel*,struct perf_sample*,char*) ; 
 int /*<<< orphan*/  print_sched_time (scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sample__fprintf_sym (struct perf_sample*,struct addr_location*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,scalar_t__ const) ; 
 int /*<<< orphan*/  stdout ; 
 TYPE_1__ symbol_conf ; 
 int task_state_char (struct thread*,int) ; 
 struct thread_runtime* thread__priv (struct thread*) ; 
 int /*<<< orphan*/  timehist_get_commstr (struct thread*) ; 
 int /*<<< orphan*/  timestamp__scnprintf_usec (scalar_t__,char*,int) ; 

__attribute__((used)) static void timehist_print_sample(struct perf_sched *sched,
				  struct evsel *evsel,
				  struct perf_sample *sample,
				  struct addr_location *al,
				  struct thread *thread,
				  u64 t, int state)
{
	struct thread_runtime *tr = thread__priv(thread);
	const char *next_comm = perf_evsel__strval(evsel, sample, "next_comm");
	const u32 next_pid = perf_evsel__intval(evsel, sample, "next_pid");
	u32 max_cpus = sched->max_cpu + 1;
	char tstr[64];
	char nstr[30];
	u64 wait_time;

	timestamp__scnprintf_usec(t, tstr, sizeof(tstr));
	printf("%15s [%04d] ", tstr, sample->cpu);

	if (sched->show_cpu_visual) {
		u32 i;
		char c;

		printf(" ");
		for (i = 0; i < max_cpus; ++i) {
			/* flag idle times with 'i'; others are sched events */
			if (i == sample->cpu)
				c = (thread->tid == 0) ? 'i' : 's';
			else
				c = ' ';
			printf("%c", c);
		}
		printf(" ");
	}

	printf(" %-*s ", comm_width, timehist_get_commstr(thread));

	wait_time = tr->dt_sleep + tr->dt_iowait + tr->dt_preempt;
	print_sched_time(wait_time, 6);

	print_sched_time(tr->dt_delay, 6);
	print_sched_time(tr->dt_run, 6);

	if (sched->show_state)
		printf(" %5c ", task_state_char(thread, state));

	if (sched->show_next) {
		snprintf(nstr, sizeof(nstr), "next: %s[%d]", next_comm, next_pid);
		printf(" %-*s", comm_width, nstr);
	}

	if (sched->show_wakeups && !sched->show_next)
		printf("  %-*s", comm_width, "");

	if (thread->tid == 0)
		goto out;

	if (sched->show_callchain)
		printf("  ");

	sample__fprintf_sym(sample, al, 0,
			    EVSEL__PRINT_SYM | EVSEL__PRINT_ONELINE |
			    EVSEL__PRINT_CALLCHAIN_ARROW |
			    EVSEL__PRINT_SKIP_IGNORED,
			    &callchain_cursor, symbol_conf.bt_stop_list,  stdout);

out:
	printf("\n");
}