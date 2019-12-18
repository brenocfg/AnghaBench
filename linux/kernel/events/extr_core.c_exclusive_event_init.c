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
 int EBUSY ; 
 int PERF_ATTACH_TASK ; 
 int /*<<< orphan*/  atomic_dec_unless_positive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_unless_negative (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_exclusive_pmu (struct pmu*) ; 

__attribute__((used)) static int exclusive_event_init(struct perf_event *event)
{
	struct pmu *pmu = event->pmu;

	if (!is_exclusive_pmu(pmu))
		return 0;

	/*
	 * Prevent co-existence of per-task and cpu-wide events on the
	 * same exclusive pmu.
	 *
	 * Negative pmu::exclusive_cnt means there are cpu-wide
	 * events on this "exclusive" pmu, positive means there are
	 * per-task events.
	 *
	 * Since this is called in perf_event_alloc() path, event::ctx
	 * doesn't exist yet; it is, however, safe to use PERF_ATTACH_TASK
	 * to mean "per-task event", because unlike other attach states it
	 * never gets cleared.
	 */
	if (event->attach_state & PERF_ATTACH_TASK) {
		if (!atomic_inc_unless_negative(&pmu->exclusive_cnt))
			return -EBUSY;
	} else {
		if (!atomic_dec_unless_positive(&pmu->exclusive_cnt))
			return -EBUSY;
	}

	return 0;
}