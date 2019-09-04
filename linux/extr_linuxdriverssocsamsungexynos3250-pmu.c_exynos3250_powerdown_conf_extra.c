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
typedef  enum sys_powerdown { ____Placeholder_sys_powerdown } sys_powerdown ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 unsigned int EXT_REGULATOR_COREBLK_DURATION ; 
 unsigned int EXT_REGULATOR_DURATION ; 
 int /*<<< orphan*/  EXYNOS3_EXT_REGULATOR_COREBLK_DURATION ; 
 int /*<<< orphan*/  EXYNOS3_EXT_REGULATOR_DURATION ; 
 unsigned int EXYNOS3_OPTION_USE_SC_COUNTER ; 
 unsigned int EXYNOS3_OPTION_USE_SC_FEEDBACK ; 
 int /*<<< orphan*/  EXYNOS3_XUSBXTI_DURATION ; 
 int /*<<< orphan*/  EXYNOS3_XXTI_DURATION ; 
 int SYS_SLEEP ; 
 unsigned int XUSBXTI_DURATION ; 
 unsigned int XXTI_DURATION ; 
 int /*<<< orphan*/ * exynos3250_list_feed ; 
 unsigned int pmu_raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_raw_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos3250_powerdown_conf_extra(enum sys_powerdown mode)
{
	unsigned int i;
	unsigned int tmp;

	/* Enable only SC_FEEDBACK */
	for (i = 0; i < ARRAY_SIZE(exynos3250_list_feed); i++) {
		tmp = pmu_raw_readl(exynos3250_list_feed[i]);
		tmp &= ~(EXYNOS3_OPTION_USE_SC_COUNTER);
		tmp |= EXYNOS3_OPTION_USE_SC_FEEDBACK;
		pmu_raw_writel(tmp, exynos3250_list_feed[i]);
	}

	if (mode != SYS_SLEEP)
		return;

	pmu_raw_writel(XUSBXTI_DURATION, EXYNOS3_XUSBXTI_DURATION);
	pmu_raw_writel(XXTI_DURATION, EXYNOS3_XXTI_DURATION);
	pmu_raw_writel(EXT_REGULATOR_DURATION, EXYNOS3_EXT_REGULATOR_DURATION);
	pmu_raw_writel(EXT_REGULATOR_COREBLK_DURATION,
		       EXYNOS3_EXT_REGULATOR_COREBLK_DURATION);
}