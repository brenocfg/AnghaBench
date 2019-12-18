#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct trace_event_file {struct trace_event_call* event_call; } ;
struct trace_event_call {TYPE_1__* class; } ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  system; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_SYSTEM ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_event_name (struct trace_event_call*) ; 

__attribute__((used)) static int t_show(struct seq_file *m, void *v)
{
	struct trace_event_file *file = v;
	struct trace_event_call *call = file->event_call;

	if (strcmp(call->class->system, TRACE_SYSTEM) != 0)
		seq_printf(m, "%s:", call->class->system);
	seq_printf(m, "%s\n", trace_event_name(call));

	return 0;
}