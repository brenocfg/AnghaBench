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
struct trace_uprobe {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_trace_uprobe (struct trace_uprobe*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int unregister_uprobe_event (struct trace_uprobe*) ; 

__attribute__((used)) static int unregister_trace_uprobe(struct trace_uprobe *tu)
{
	int ret;

	ret = unregister_uprobe_event(tu);
	if (ret)
		return ret;

	list_del(&tu->list);
	free_trace_uprobe(tu);
	return 0;
}