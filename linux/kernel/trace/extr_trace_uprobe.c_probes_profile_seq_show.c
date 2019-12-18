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
struct trace_uprobe {int /*<<< orphan*/  nhit; int /*<<< orphan*/  tp; int /*<<< orphan*/  filename; } ;
struct seq_file {int dummy; } ;
struct dyn_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_trace_uprobe (struct dyn_event*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct trace_uprobe* to_trace_uprobe (struct dyn_event*) ; 
 int /*<<< orphan*/  trace_probe_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int probes_profile_seq_show(struct seq_file *m, void *v)
{
	struct dyn_event *ev = v;
	struct trace_uprobe *tu;

	if (!is_trace_uprobe(ev))
		return 0;

	tu = to_trace_uprobe(ev);
	seq_printf(m, "  %s %-44s %15lu\n", tu->filename,
			trace_probe_name(&tu->tp), tu->nhit);
	return 0;
}