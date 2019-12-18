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
struct TYPE_4__ {struct trace_probe_event* print_fmt; struct trace_probe_event* name; } ;
struct TYPE_3__ {struct trace_probe_event* system; } ;
struct trace_probe_event {TYPE_2__ call; TYPE_1__ class; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct trace_probe_event*) ; 

__attribute__((used)) static void trace_probe_event_free(struct trace_probe_event *tpe)
{
	kfree(tpe->class.system);
	kfree(tpe->call.name);
	kfree(tpe->call.print_fmt);
	kfree(tpe);
}