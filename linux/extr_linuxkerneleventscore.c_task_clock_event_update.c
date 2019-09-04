#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_2__ {int /*<<< orphan*/  prev_count; } ;
struct perf_event {int /*<<< orphan*/  count; TYPE_1__ hw; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  local64_add (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ local64_xchg (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void task_clock_event_update(struct perf_event *event, u64 now)
{
	u64 prev;
	s64 delta;

	prev = local64_xchg(&event->hw.prev_count, now);
	delta = now - prev;
	local64_add(delta, &event->count);
}