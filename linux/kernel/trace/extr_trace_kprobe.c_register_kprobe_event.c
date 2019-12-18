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
struct trace_kprobe {int /*<<< orphan*/  tp; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_trace_event_call (struct trace_kprobe*) ; 
 int trace_probe_register_event_call (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int register_kprobe_event(struct trace_kprobe *tk)
{
	init_trace_event_call(tk);

	return trace_probe_register_event_call(&tk->tp);
}