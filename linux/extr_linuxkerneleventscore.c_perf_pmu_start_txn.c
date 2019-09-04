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
struct pmu {int dummy; } ;

/* Variables and functions */
 unsigned int PERF_PMU_TXN_ADD ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nop_txn_flags ; 
 int /*<<< orphan*/  perf_pmu_disable (struct pmu*) ; 

__attribute__((used)) static void perf_pmu_start_txn(struct pmu *pmu, unsigned int flags)
{
	__this_cpu_write(nop_txn_flags, flags);

	if (flags & ~PERF_PMU_TXN_ADD)
		return;

	perf_pmu_disable(pmu);
}