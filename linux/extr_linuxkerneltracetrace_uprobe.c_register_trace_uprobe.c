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
struct trace_uprobe {int /*<<< orphan*/  list; TYPE_2__ tp; } ;
struct TYPE_4__ {int /*<<< orphan*/  system; } ;

/* Variables and functions */
 struct trace_uprobe* find_probe_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int register_uprobe_event (struct trace_uprobe*) ; 
 int /*<<< orphan*/  trace_event_name (TYPE_3__*) ; 
 int unregister_trace_uprobe (struct trace_uprobe*) ; 
 int /*<<< orphan*/  uprobe_list ; 
 int /*<<< orphan*/  uprobe_lock ; 

__attribute__((used)) static int register_trace_uprobe(struct trace_uprobe *tu)
{
	struct trace_uprobe *old_tu;
	int ret;

	mutex_lock(&uprobe_lock);

	/* register as an event */
	old_tu = find_probe_event(trace_event_name(&tu->tp.call),
			tu->tp.call.class->system);
	if (old_tu) {
		/* delete old event */
		ret = unregister_trace_uprobe(old_tu);
		if (ret)
			goto end;
	}

	ret = register_uprobe_event(tu);
	if (ret) {
		pr_warn("Failed to register probe event(%d)\n", ret);
		goto end;
	}

	list_add_tail(&tu->list, &uprobe_list);

end:
	mutex_unlock(&uprobe_lock);

	return ret;
}