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
struct pmu {int (* filter_match ) (struct perf_event*) ;} ;
struct perf_event {struct pmu* pmu; } ;

/* Variables and functions */
 int stub1 (struct perf_event*) ; 

__attribute__((used)) static inline int __pmu_filter_match(struct perf_event *event)
{
	struct pmu *pmu = event->pmu;
	return pmu->filter_match ? pmu->filter_match(event) : 1;
}