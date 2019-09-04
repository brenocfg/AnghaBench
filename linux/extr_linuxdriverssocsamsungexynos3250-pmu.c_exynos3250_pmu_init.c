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

/* Variables and functions */
 int /*<<< orphan*/  EXYNOS3_ARM_COMMON_OPTION ; 
 unsigned int EXYNOS3_OPTION_SKIP_DEACTIVATE_ACEACP_IN_PWDN ; 
 int /*<<< orphan*/  S5P_CENTRAL_SEQ_OPTION ; 
 int /*<<< orphan*/  S5P_PS_HOLD_CONTROL ; 
 unsigned int S5P_PS_HOLD_EN ; 
 unsigned int S5P_PS_HOLD_OUTPUT_HIGH ; 
 unsigned int S5P_USE_STANDBY_WFI_ALL ; 
 unsigned int pmu_raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_raw_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos3250_pmu_init(void)
{
	unsigned int value;

	/*
	 * To prevent from issuing new bus request form L2 memory system
	 * If core status is power down, should be set '1' to L2 power down
	 */
	value = pmu_raw_readl(EXYNOS3_ARM_COMMON_OPTION);
	value |= EXYNOS3_OPTION_SKIP_DEACTIVATE_ACEACP_IN_PWDN;
	pmu_raw_writel(value, EXYNOS3_ARM_COMMON_OPTION);

	/* Enable USE_STANDBY_WFI for all CORE */
	pmu_raw_writel(S5P_USE_STANDBY_WFI_ALL, S5P_CENTRAL_SEQ_OPTION);

	/*
	 * Set PSHOLD port for output high
	 */
	value = pmu_raw_readl(S5P_PS_HOLD_CONTROL);
	value |= S5P_PS_HOLD_OUTPUT_HIGH;
	pmu_raw_writel(value, S5P_PS_HOLD_CONTROL);

	/*
	 * Enable signal for PSHOLD port
	 */
	value = pmu_raw_readl(S5P_PS_HOLD_CONTROL);
	value |= S5P_PS_HOLD_EN;
	pmu_raw_writel(value, S5P_PS_HOLD_CONTROL);
}