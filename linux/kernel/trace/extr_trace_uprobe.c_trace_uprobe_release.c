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
struct trace_uprobe {int dummy; } ;
struct dyn_event {int dummy; } ;

/* Variables and functions */
 struct trace_uprobe* to_trace_uprobe (struct dyn_event*) ; 
 int unregister_trace_uprobe (struct trace_uprobe*) ; 

__attribute__((used)) static int trace_uprobe_release(struct dyn_event *ev)
{
	struct trace_uprobe *tu = to_trace_uprobe(ev);

	return unregister_trace_uprobe(tu);
}