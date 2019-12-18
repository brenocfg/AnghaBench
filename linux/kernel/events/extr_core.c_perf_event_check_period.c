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
typedef  int /*<<< orphan*/  u64 ;
struct perf_event {TYPE_1__* pmu; } ;
struct TYPE_2__ {int (* check_period ) (struct perf_event*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct perf_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_event_check_period(struct perf_event *event, u64 value)
{
	return event->pmu->check_period(event, value);
}