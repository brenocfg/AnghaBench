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
 int /*<<< orphan*/  DIFF_ARG_TYPE ; 
 int EEXIST ; 
 int /*<<< orphan*/  SAME_PROBE ; 
 int /*<<< orphan*/  dyn_event_add (int /*<<< orphan*/ *) ; 
 int trace_probe_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int trace_probe_compare_arg_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_probe_log_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_probe_log_set_index (int) ; 
 scalar_t__ trace_uprobe_has_same_uprobe (struct trace_uprobe*,struct trace_uprobe*) ; 

__attribute__((used)) static int append_trace_uprobe(struct trace_uprobe *tu, struct trace_uprobe *to)
{
	int ret;

	ret = trace_probe_compare_arg_type(&tu->tp, &to->tp);
	if (ret) {
		/* Note that argument starts index = 2 */
		trace_probe_log_set_index(ret + 1);
		trace_probe_log_err(0, DIFF_ARG_TYPE);
		return -EEXIST;
	}
	if (trace_uprobe_has_same_uprobe(to, tu)) {
		trace_probe_log_set_index(0);
		trace_probe_log_err(0, SAME_PROBE);
		return -EEXIST;
	}

	/* Append to existing event */
	ret = trace_probe_append(&tu->tp, &to->tp);
	if (!ret)
		dyn_event_add(&tu->devent);

	return ret;
}