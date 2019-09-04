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
struct dsu_pmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dsu_pmu_counter_interrupt_enable (int) ; 
 int /*<<< orphan*/  __dsu_pmu_enable_counter (int) ; 

__attribute__((used)) static void dsu_pmu_enable_counter(struct dsu_pmu *dsu_pmu, int idx)
{
	__dsu_pmu_counter_interrupt_enable(idx);
	__dsu_pmu_enable_counter(idx);
}