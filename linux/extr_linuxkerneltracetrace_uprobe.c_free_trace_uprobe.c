#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct trace_uprobe* name; TYPE_1__* class; } ;
struct TYPE_6__ {int nr_args; TYPE_2__ call; int /*<<< orphan*/ * args; } ;
struct trace_uprobe {struct trace_uprobe* filename; TYPE_3__ tp; int /*<<< orphan*/  path; } ;
struct TYPE_4__ {struct trace_uprobe* system; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct trace_uprobe*) ; 
 int /*<<< orphan*/  path_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  traceprobe_free_probe_arg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_trace_uprobe(struct trace_uprobe *tu)
{
	int i;

	for (i = 0; i < tu->tp.nr_args; i++)
		traceprobe_free_probe_arg(&tu->tp.args[i]);

	path_put(&tu->path);
	kfree(tu->tp.call.class->system);
	kfree(tu->tp.call.name);
	kfree(tu->filename);
	kfree(tu);
}