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
struct trace_kprobe {int dummy; } ;
struct dyn_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_trace_kprobe (struct trace_kprobe*) ; 
 struct trace_kprobe* to_trace_kprobe (struct dyn_event*) ; 
 int unregister_trace_kprobe (struct trace_kprobe*) ; 

__attribute__((used)) static int trace_kprobe_release(struct dyn_event *ev)
{
	struct trace_kprobe *tk = to_trace_kprobe(ev);
	int ret = unregister_trace_kprobe(tk);

	if (!ret)
		free_trace_kprobe(tk);
	return ret;
}