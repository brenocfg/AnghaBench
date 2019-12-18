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
struct pmu {int /*<<< orphan*/  exclusive_cnt; } ;
struct perf_event {int attach_state; struct pmu* pmu; } ;

/* Variables and functions */
 int PERF_ATTACH_TASK ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_exclusive_pmu (struct pmu*) ; 

__attribute__((used)) static void exclusive_event_destroy(struct perf_event *event)
{
	struct pmu *pmu = event->pmu;

	if (!is_exclusive_pmu(pmu))
		return;

	/* see comment in exclusive_event_init() */
	if (event->attach_state & PERF_ATTACH_TASK)
		atomic_dec(&pmu->exclusive_cnt);
	else
		atomic_inc(&pmu->exclusive_cnt);
}