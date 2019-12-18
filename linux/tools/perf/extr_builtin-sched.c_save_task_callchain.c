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
struct symbol {int ignore; int /*<<< orphan*/  name; } ;
struct perf_sched {scalar_t__ max_stack; int /*<<< orphan*/  show_callchain; } ;
struct perf_sample {int /*<<< orphan*/ * callchain; int /*<<< orphan*/  pid; } ;
struct machine {int dummy; } ;
struct evsel {int dummy; } ;
struct callchain_cursor_node {struct symbol* sym; } ;
struct callchain_cursor {int dummy; } ;

/* Variables and functions */
 struct callchain_cursor callchain_cursor ; 
 int /*<<< orphan*/  callchain_cursor_advance (struct callchain_cursor*) ; 
 int /*<<< orphan*/  callchain_cursor_commit (struct callchain_cursor*) ; 
 struct callchain_cursor_node* callchain_cursor_current (struct callchain_cursor*) ; 
 struct thread* machine__findnew_thread (struct machine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ thread__resolve_callchain (struct thread*,struct callchain_cursor*,struct evsel*,struct perf_sample*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void save_task_callchain(struct perf_sched *sched,
				struct perf_sample *sample,
				struct evsel *evsel,
				struct machine *machine)
{
	struct callchain_cursor *cursor = &callchain_cursor;
	struct thread *thread;

	/* want main thread for process - has maps */
	thread = machine__findnew_thread(machine, sample->pid, sample->pid);
	if (thread == NULL) {
		pr_debug("Failed to get thread for pid %d.\n", sample->pid);
		return;
	}

	if (!sched->show_callchain || sample->callchain == NULL)
		return;

	if (thread__resolve_callchain(thread, cursor, evsel, sample,
				      NULL, NULL, sched->max_stack + 2) != 0) {
		if (verbose > 0)
			pr_err("Failed to resolve callchain. Skipping\n");

		return;
	}

	callchain_cursor_commit(cursor);

	while (true) {
		struct callchain_cursor_node *node;
		struct symbol *sym;

		node = callchain_cursor_current(cursor);
		if (node == NULL)
			break;

		sym = node->sym;
		if (sym) {
			if (!strcmp(sym->name, "schedule") ||
			    !strcmp(sym->name, "__schedule") ||
			    !strcmp(sym->name, "preempt_schedule"))
				sym->ignore = 1;
		}

		callchain_cursor_advance(cursor);
	}
}