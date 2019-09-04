#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  kp; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  files; } ;
struct trace_kprobe {int /*<<< orphan*/  list; TYPE_4__ rp; TYPE_1__ tp; } ;
struct trace_event_file {int dummy; } ;
struct event_file_link {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TP_FLAG_PROFILE ; 
 int /*<<< orphan*/  TP_FLAG_TRACE ; 
 int /*<<< orphan*/  disable_kprobe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_kretprobe (TYPE_4__*) ; 
 struct event_file_link* find_event_file_link (TYPE_1__*,struct trace_event_file*) ; 
 int /*<<< orphan*/  kfree (struct event_file_link*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_sched () ; 
 scalar_t__ trace_kprobe_is_return (struct trace_kprobe*) ; 
 int /*<<< orphan*/  trace_probe_is_enabled (TYPE_1__*) ; 
 scalar_t__ trace_probe_is_registered (TYPE_1__*) ; 

__attribute__((used)) static int
disable_trace_kprobe(struct trace_kprobe *tk, struct trace_event_file *file)
{
	struct event_file_link *link = NULL;
	int wait = 0;
	int ret = 0;

	if (file) {
		link = find_event_file_link(&tk->tp, file);
		if (!link) {
			ret = -EINVAL;
			goto out;
		}

		list_del_rcu(&link->list);
		wait = 1;
		if (!list_empty(&tk->tp.files))
			goto out;

		tk->tp.flags &= ~TP_FLAG_TRACE;
	} else
		tk->tp.flags &= ~TP_FLAG_PROFILE;

	if (!trace_probe_is_enabled(&tk->tp) && trace_probe_is_registered(&tk->tp)) {
		if (trace_kprobe_is_return(tk))
			disable_kretprobe(&tk->rp);
		else
			disable_kprobe(&tk->rp.kp);
		wait = 1;
	}

	/*
	 * if tk is not added to any list, it must be a local trace_kprobe
	 * created with perf_event_open. We don't need to wait for these
	 * trace_kprobes
	 */
	if (list_empty(&tk->list))
		wait = 0;
 out:
	if (wait) {
		/*
		 * Synchronize with kprobe_trace_func/kretprobe_trace_func
		 * to ensure disabled (all running handlers are finished).
		 * This is not only for kfree(), but also the caller,
		 * trace_remove_event_call() supposes it for releasing
		 * event_call related objects, which will be accessed in
		 * the kprobe_trace_func/kretprobe_trace_func.
		 */
		synchronize_sched();
		kfree(link);	/* Ignored if link == NULL */
	}

	return ret;
}