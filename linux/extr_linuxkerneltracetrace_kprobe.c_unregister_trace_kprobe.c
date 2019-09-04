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
struct trace_kprobe {int /*<<< orphan*/  list; int /*<<< orphan*/  tp; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  __unregister_trace_kprobe (struct trace_kprobe*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ trace_probe_is_enabled (int /*<<< orphan*/ *) ; 
 scalar_t__ unregister_kprobe_event (struct trace_kprobe*) ; 

__attribute__((used)) static int unregister_trace_kprobe(struct trace_kprobe *tk)
{
	/* Enabled event can not be unregistered */
	if (trace_probe_is_enabled(&tk->tp))
		return -EBUSY;

	/* Will fail if probe is being used by ftrace or perf */
	if (unregister_kprobe_event(tk))
		return -EBUSY;

	__unregister_trace_kprobe(tk);
	list_del(&tk->list);

	return 0;
}