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
struct trace_uprobe {int /*<<< orphan*/  devent; int /*<<< orphan*/  tp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_PROBE_TYPE ; 
 int EEXIST ; 
 int append_trace_uprobe (struct trace_uprobe*,struct trace_uprobe*) ; 
 int /*<<< orphan*/  dyn_event_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_mutex ; 
 struct trace_uprobe* find_probe_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_ret_probe (struct trace_uprobe*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int register_uprobe_event (struct trace_uprobe*) ; 
 int /*<<< orphan*/  trace_probe_group_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_probe_log_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_probe_log_set_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_probe_name (int /*<<< orphan*/ *) ; 
 int validate_ref_ctr_offset (struct trace_uprobe*) ; 

__attribute__((used)) static int register_trace_uprobe(struct trace_uprobe *tu)
{
	struct trace_uprobe *old_tu;
	int ret;

	mutex_lock(&event_mutex);

	ret = validate_ref_ctr_offset(tu);
	if (ret)
		goto end;

	/* register as an event */
	old_tu = find_probe_event(trace_probe_name(&tu->tp),
				  trace_probe_group_name(&tu->tp));
	if (old_tu) {
		if (is_ret_probe(tu) != is_ret_probe(old_tu)) {
			trace_probe_log_set_index(0);
			trace_probe_log_err(0, DIFF_PROBE_TYPE);
			ret = -EEXIST;
		} else {
			ret = append_trace_uprobe(tu, old_tu);
		}
		goto end;
	}

	ret = register_uprobe_event(tu);
	if (ret) {
		pr_warn("Failed to register probe event(%d)\n", ret);
		goto end;
	}

	dyn_event_add(&tu->devent);

end:
	mutex_unlock(&event_mutex);

	return ret;
}