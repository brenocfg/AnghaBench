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
struct perf_event {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ PERF_EVENT_STATE_DEAD ; 

__attribute__((used)) static bool is_orphaned_event(struct perf_event *event)
{
	return event->state == PERF_EVENT_STATE_DEAD;
}