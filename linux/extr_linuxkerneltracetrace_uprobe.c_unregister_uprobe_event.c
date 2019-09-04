#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * print_fmt; } ;
struct TYPE_3__ {TYPE_2__ call; } ;
struct trace_uprobe {TYPE_1__ tp; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int trace_remove_event_call (TYPE_2__*) ; 

__attribute__((used)) static int unregister_uprobe_event(struct trace_uprobe *tu)
{
	int ret;

	/* tu->event is unregistered in trace_remove_event_call() */
	ret = trace_remove_event_call(&tu->tp.call);
	if (ret)
		return ret;
	kfree(tu->tp.call.print_fmt);
	tu->tp.call.print_fmt = NULL;
	return 0;
}