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
struct trace_probe {int dummy; } ;
struct trace_event_file {int dummy; } ;
struct trace_event_call {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int /*<<< orphan*/  TP_FLAG_PROFILE ; 
 int /*<<< orphan*/  TP_FLAG_TRACE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __disable_trace_kprobe (struct trace_probe*) ; 
 int /*<<< orphan*/  trace_probe_clear_flag (struct trace_probe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_probe_get_file_link (struct trace_probe*,struct trace_event_file*) ; 
 int /*<<< orphan*/  trace_probe_has_single_file (struct trace_probe*) ; 
 int /*<<< orphan*/  trace_probe_is_enabled (struct trace_probe*) ; 
 struct trace_probe* trace_probe_primary_from_call (struct trace_event_call*) ; 
 int /*<<< orphan*/  trace_probe_remove_file (struct trace_probe*,struct trace_event_file*) ; 

__attribute__((used)) static int disable_trace_kprobe(struct trace_event_call *call,
				struct trace_event_file *file)
{
	struct trace_probe *tp;

	tp = trace_probe_primary_from_call(call);
	if (WARN_ON_ONCE(!tp))
		return -ENODEV;

	if (file) {
		if (!trace_probe_get_file_link(tp, file))
			return -ENOENT;
		if (!trace_probe_has_single_file(tp))
			goto out;
		trace_probe_clear_flag(tp, TP_FLAG_TRACE);
	} else
		trace_probe_clear_flag(tp, TP_FLAG_PROFILE);

	if (!trace_probe_is_enabled(tp))
		__disable_trace_kprobe(tp);

 out:
	if (file)
		/*
		 * Synchronization is done in below function. For perf event,
		 * file == NULL and perf_trace_event_unreg() calls
		 * tracepoint_synchronize_unregister() to ensure synchronize
		 * event. We don't need to care about it.
		 */
		trace_probe_remove_file(tp, file);

	return 0;
}