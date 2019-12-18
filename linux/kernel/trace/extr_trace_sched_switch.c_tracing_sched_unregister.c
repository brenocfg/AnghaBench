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

/* Variables and functions */
 int /*<<< orphan*/  probe_sched_switch ; 
 int /*<<< orphan*/  probe_sched_wakeup ; 
 int /*<<< orphan*/  unregister_trace_sched_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_trace_sched_wakeup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_trace_sched_wakeup_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tracing_sched_unregister(void)
{
	unregister_trace_sched_switch(probe_sched_switch, NULL);
	unregister_trace_sched_wakeup_new(probe_sched_wakeup, NULL);
	unregister_trace_sched_wakeup(probe_sched_wakeup, NULL);
}