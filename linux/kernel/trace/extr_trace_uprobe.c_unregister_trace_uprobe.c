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
struct trace_uprobe {int /*<<< orphan*/  tp; int /*<<< orphan*/  devent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dyn_event_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_trace_uprobe (struct trace_uprobe*) ; 
 scalar_t__ trace_probe_has_sibling (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_probe_unlink (int /*<<< orphan*/ *) ; 
 int unregister_uprobe_event (struct trace_uprobe*) ; 

__attribute__((used)) static int unregister_trace_uprobe(struct trace_uprobe *tu)
{
	int ret;

	if (trace_probe_has_sibling(&tu->tp))
		goto unreg;

	ret = unregister_uprobe_event(tu);
	if (ret)
		return ret;

unreg:
	dyn_event_remove(&tu->devent);
	trace_probe_unlink(&tu->tp);
	free_trace_uprobe(tu);
	return 0;
}