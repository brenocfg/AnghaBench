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
struct perf_event {int /*<<< orphan*/  attach_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_ATTACH_ITRACE ; 

void perf_event_itrace_started(struct perf_event *event)
{
	event->attach_state |= PERF_ATTACH_ITRACE;
}