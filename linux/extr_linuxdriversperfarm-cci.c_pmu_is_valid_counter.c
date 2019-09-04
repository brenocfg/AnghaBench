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
struct cci_pmu {int dummy; } ;

/* Variables and functions */
 int CCI_PMU_CNTR_LAST (struct cci_pmu*) ; 

__attribute__((used)) static int pmu_is_valid_counter(struct cci_pmu *cci_pmu, int idx)
{
	return 0 <= idx && idx <= CCI_PMU_CNTR_LAST(cci_pmu);
}