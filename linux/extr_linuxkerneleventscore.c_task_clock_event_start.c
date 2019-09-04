#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  prev_count; } ;
struct perf_event {TYPE_2__* ctx; TYPE_1__ hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  time; } ;

/* Variables and functions */
 int /*<<< orphan*/  local64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_swevent_start_hrtimer (struct perf_event*) ; 

__attribute__((used)) static void task_clock_event_start(struct perf_event *event, int flags)
{
	local64_set(&event->hw.prev_count, event->ctx->time);
	perf_swevent_start_hrtimer(event);
}