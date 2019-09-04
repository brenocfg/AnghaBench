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
struct perf_event {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_read (struct perf_event*,int) ; 
 int /*<<< orphan*/  perf_event_update_userpage (struct perf_event*) ; 

__attribute__((used)) static void _perf_event_reset(struct perf_event *event)
{
	(void)perf_event_read(event, false);
	local64_set(&event->count, 0);
	perf_event_update_userpage(event);
}