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
typedef  enum sys_powerdown { ____Placeholder_sys_powerdown } sys_powerdown ;

/* Variables and functions */
 int /*<<< orphan*/  EXYNOS_IROM_DATA2 ; 
 int /*<<< orphan*/  MPIDR_AFFINITY_LEVEL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmu_raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_cpuid_mpidr () ; 

__attribute__((used)) static void exynos5420_powerdown_conf(enum sys_powerdown mode)
{
	u32 this_cluster;

	this_cluster = MPIDR_AFFINITY_LEVEL(read_cpuid_mpidr(), 1);

	/*
	 * set the cluster id to IROM register to ensure that we wake
	 * up with the current cluster.
	 */
	pmu_raw_writel(this_cluster, EXYNOS_IROM_DATA2);
}