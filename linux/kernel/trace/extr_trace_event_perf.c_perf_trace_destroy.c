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
struct perf_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_trace_event_close (struct perf_event*) ; 
 int /*<<< orphan*/  perf_trace_event_unreg (struct perf_event*) ; 

void perf_trace_destroy(struct perf_event *p_event)
{
	mutex_lock(&event_mutex);
	perf_trace_event_close(p_event);
	perf_trace_event_unreg(p_event);
	mutex_unlock(&event_mutex);
}