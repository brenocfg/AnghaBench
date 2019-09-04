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
 int /*<<< orphan*/  EXYNOS5_ARM_COMMON_OPTION ; 
 unsigned int EXYNOS5_OPTION_USE_STANDBYWFE ; 
 unsigned int EXYNOS5_OPTION_USE_STANDBYWFI ; 
 unsigned int EXYNOS5_SKIP_DEACTIVATE_ACEACP_IN_PWDN ; 
 unsigned int EXYNOS5_USE_SC_COUNTER ; 
 unsigned int EXYNOS5_USE_SC_FEEDBACK ; 
 int /*<<< orphan*/ * exynos5_list_both_cnt_feed ; 
 int /*<<< orphan*/ * exynos5_list_disable_wfi_wfe ; 
 unsigned int pmu_raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_raw_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos5_powerdown_conf(enum sys_powerdown mode)
{
	unsigned int i;
	unsigned int tmp;

	/*
	 * Enable both SC_FEEDBACK and SC_COUNTER
	 */
	for (i = 0; i < ARRAY_SIZE(exynos5_list_both_cnt_feed); i++) {
		tmp = pmu_raw_readl(exynos5_list_both_cnt_feed[i]);
		tmp |= (EXYNOS5_USE_SC_FEEDBACK |
			EXYNOS5_USE_SC_COUNTER);
		pmu_raw_writel(tmp, exynos5_list_both_cnt_feed[i]);
	}

	/*
	 * SKIP_DEACTIVATE_ACEACP_IN_PWDN_BITFIELD Enable
	 */
	tmp = pmu_raw_readl(EXYNOS5_ARM_COMMON_OPTION);
	tmp |= EXYNOS5_SKIP_DEACTIVATE_ACEACP_IN_PWDN;
	pmu_raw_writel(tmp, EXYNOS5_ARM_COMMON_OPTION);

	/*
	 * Disable WFI/WFE on XXX_OPTION
	 */
	for (i = 0; i < ARRAY_SIZE(exynos5_list_disable_wfi_wfe); i++) {
		tmp = pmu_raw_readl(exynos5_list_disable_wfi_wfe[i]);
		tmp &= ~(EXYNOS5_OPTION_USE_STANDBYWFE |
			 EXYNOS5_OPTION_USE_STANDBYWFI);
		pmu_raw_writel(tmp, exynos5_list_disable_wfi_wfe[i]);
	}
}