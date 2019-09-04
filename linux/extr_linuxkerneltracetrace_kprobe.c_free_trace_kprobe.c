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
struct TYPE_6__ {struct trace_kprobe* name; TYPE_1__* class; } ;
struct TYPE_5__ {int nr_args; TYPE_3__ call; int /*<<< orphan*/ * args; } ;
struct trace_kprobe {int /*<<< orphan*/  nhit; struct trace_kprobe* symbol; TYPE_2__ tp; } ;
struct TYPE_4__ {struct trace_kprobe* system; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct trace_kprobe*) ; 
 int /*<<< orphan*/  traceprobe_free_probe_arg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_trace_kprobe(struct trace_kprobe *tk)
{
	int i;

	for (i = 0; i < tk->tp.nr_args; i++)
		traceprobe_free_probe_arg(&tk->tp.args[i]);

	kfree(tk->tp.call.class->system);
	kfree(tk->tp.call.name);
	kfree(tk->symbol);
	free_percpu(tk->nhit);
	kfree(tk);
}