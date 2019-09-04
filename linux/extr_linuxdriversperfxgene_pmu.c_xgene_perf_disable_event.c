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
struct xgene_pmu_dev {struct xgene_pmu* parent; } ;
struct xgene_pmu {TYPE_1__* ops; } ;
struct perf_event {int /*<<< orphan*/  pmu; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable_counter_int ) (struct xgene_pmu_dev*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* disable_counter ) (struct xgene_pmu_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GET_CNTR (struct perf_event*) ; 
 int /*<<< orphan*/  stub1 (struct xgene_pmu_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct xgene_pmu_dev*,int /*<<< orphan*/ ) ; 
 struct xgene_pmu_dev* to_pmu_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_perf_disable_event(struct perf_event *event)
{
	struct xgene_pmu_dev *pmu_dev = to_pmu_dev(event->pmu);
	struct xgene_pmu *xgene_pmu = pmu_dev->parent;

	xgene_pmu->ops->disable_counter(pmu_dev, GET_CNTR(event));
	xgene_pmu->ops->disable_counter_int(pmu_dev, GET_CNTR(event));
}