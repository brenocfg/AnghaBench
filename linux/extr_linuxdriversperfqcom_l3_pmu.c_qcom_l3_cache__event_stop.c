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
struct hw_perf_event {int state; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct l3cache_event_ops {int /*<<< orphan*/  (* update ) (struct perf_event*) ;int /*<<< orphan*/  (* stop ) (struct perf_event*,int) ;} ;

/* Variables and functions */
 int PERF_EF_UPDATE ; 
 int PERF_HES_STOPPED ; 
 int PERF_HES_UPTODATE ; 
 struct l3cache_event_ops* l3cache_event_get_ops (struct perf_event*) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*,int) ; 
 int /*<<< orphan*/  stub2 (struct perf_event*) ; 

__attribute__((used)) static void qcom_l3_cache__event_stop(struct perf_event *event, int flags)
{
	struct hw_perf_event *hwc = &event->hw;
	const struct l3cache_event_ops *ops = l3cache_event_get_ops(event);

	if (hwc->state & PERF_HES_STOPPED)
		return;

	ops->stop(event, flags);
	if (flags & PERF_EF_UPDATE)
		ops->update(event);
	hwc->state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
}