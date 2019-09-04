#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* class; } ;
struct TYPE_5__ {TYPE_3__ call; } ;
struct trace_kprobe {int /*<<< orphan*/  list; TYPE_2__ tp; } ;
struct TYPE_4__ {int /*<<< orphan*/  system; } ;

/* Variables and functions */
 int ENOENT ; 
 int __register_trace_kprobe (struct trace_kprobe*) ; 
 struct trace_kprobe* find_trace_kprobe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_trace_kprobe (struct trace_kprobe*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  probe_list ; 
 int /*<<< orphan*/  probe_lock ; 
 int register_kprobe_event (struct trace_kprobe*) ; 
 int /*<<< orphan*/  trace_event_name (TYPE_3__*) ; 
 int /*<<< orphan*/  trace_kprobe_module_exist (struct trace_kprobe*) ; 
 int /*<<< orphan*/  unregister_kprobe_event (struct trace_kprobe*) ; 
 int unregister_trace_kprobe (struct trace_kprobe*) ; 

__attribute__((used)) static int register_trace_kprobe(struct trace_kprobe *tk)
{
	struct trace_kprobe *old_tk;
	int ret;

	mutex_lock(&probe_lock);

	/* Delete old (same name) event if exist */
	old_tk = find_trace_kprobe(trace_event_name(&tk->tp.call),
			tk->tp.call.class->system);
	if (old_tk) {
		ret = unregister_trace_kprobe(old_tk);
		if (ret < 0)
			goto end;
		free_trace_kprobe(old_tk);
	}

	/* Register new event */
	ret = register_kprobe_event(tk);
	if (ret) {
		pr_warn("Failed to register probe event(%d)\n", ret);
		goto end;
	}

	/* Register k*probe */
	ret = __register_trace_kprobe(tk);
	if (ret == -ENOENT && !trace_kprobe_module_exist(tk)) {
		pr_warn("This probe might be able to register after target module is loaded. Continue.\n");
		ret = 0;
	}

	if (ret < 0)
		unregister_kprobe_event(tk);
	else
		list_add_tail(&tk->list, &probe_list);

end:
	mutex_unlock(&probe_lock);
	return ret;
}