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
struct seq_file {int dummy; } ;
struct dyn_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_trace_uprobe (struct dyn_event*) ; 
 int trace_uprobe_show (struct seq_file*,struct dyn_event*) ; 

__attribute__((used)) static int probes_seq_show(struct seq_file *m, void *v)
{
	struct dyn_event *ev = v;

	if (!is_trace_uprobe(ev))
		return 0;

	return trace_uprobe_show(m, ev);
}