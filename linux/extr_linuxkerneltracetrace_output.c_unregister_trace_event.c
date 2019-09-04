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
struct trace_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __unregister_trace_event (struct trace_event*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_event_sem ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int unregister_trace_event(struct trace_event *event)
{
	down_write(&trace_event_sem);
	__unregister_trace_event(event);
	up_write(&trace_event_sem);

	return 0;
}