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
struct TYPE_4__ {scalar_t__ addr_filters_gen; } ;
struct perf_event {scalar_t__ addr_filters_gen; TYPE_2__ hw; TYPE_1__* pmu; } ;
struct perf_addr_filters_head {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* addr_filters_sync ) (struct perf_event*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  has_addr_filter (struct perf_event*) ; 
 struct perf_addr_filters_head* perf_event_addr_filters (struct perf_event*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*) ; 

void perf_event_addr_filters_sync(struct perf_event *event)
{
	struct perf_addr_filters_head *ifh = perf_event_addr_filters(event);

	if (!has_addr_filter(event))
		return;

	raw_spin_lock(&ifh->lock);
	if (event->addr_filters_gen != event->hw.addr_filters_gen) {
		event->pmu->addr_filters_sync(event);
		event->hw.addr_filters_gen = event->addr_filters_gen;
	}
	raw_spin_unlock(&ifh->lock);
}