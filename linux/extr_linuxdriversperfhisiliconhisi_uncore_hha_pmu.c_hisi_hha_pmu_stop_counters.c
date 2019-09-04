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
typedef  int /*<<< orphan*/  u32 ;
struct hisi_pmu {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ HHA_PERF_CTRL ; 
 int /*<<< orphan*/  HHA_PERF_CTRL_EN ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hisi_hha_pmu_stop_counters(struct hisi_pmu *hha_pmu)
{
	u32 val;

	/*
	 * Clear perf_enable bit in HHA_PERF_CTRL to stop event
	 * counting for all enabled counters.
	 */
	val = readl(hha_pmu->base + HHA_PERF_CTRL);
	val &= ~(HHA_PERF_CTRL_EN);
	writel(val, hha_pmu->base + HHA_PERF_CTRL);
}