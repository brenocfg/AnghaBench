#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int s3entry_method; scalar_t__ aon_ctrl_base; scalar_t__ aon_sram; } ;

/* Variables and functions */
 scalar_t__ AON_CTRL_PM_CPU_WAIT_COUNT ; 
 scalar_t__ AON_REG_MAGIC_FLAGS ; 
 int /*<<< orphan*/  M1_PM_COLD_CONFIG ; 
 int /*<<< orphan*/  PM_COLD_CONFIG ; 
 int PWRDWN_SEQ_POWERDOWN_PLL ; 
 int /*<<< orphan*/  SHIMPHY_PAD_S3_PWRDWN_SEQ_MASK ; 
 int SHIMPHY_PAD_S3_PWRDWN_SEQ_SHIFT ; 
 int /*<<< orphan*/  brcmstb_do_pmsm_power_down (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcmstb_pm_handshake () ; 
 TYPE_1__ ctrl ; 
 int /*<<< orphan*/  ddr_ctrl_set (int) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  shimphy_set (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void brcmstb_pm_poweroff(void)
{
	brcmstb_pm_handshake();

	/* Clear magic S3 warm-boot value */
	writel_relaxed(0, ctrl.aon_sram + AON_REG_MAGIC_FLAGS);
	(void)readl_relaxed(ctrl.aon_sram + AON_REG_MAGIC_FLAGS);

	/* Skip wait-for-interrupt signal; just use a countdown */
	writel_relaxed(0x10, ctrl.aon_ctrl_base + AON_CTRL_PM_CPU_WAIT_COUNT);
	(void)readl_relaxed(ctrl.aon_ctrl_base + AON_CTRL_PM_CPU_WAIT_COUNT);

	if (ctrl.s3entry_method == 1) {
		shimphy_set((PWRDWN_SEQ_POWERDOWN_PLL <<
			     SHIMPHY_PAD_S3_PWRDWN_SEQ_SHIFT),
			     ~SHIMPHY_PAD_S3_PWRDWN_SEQ_MASK);
		ddr_ctrl_set(false);
		brcmstb_do_pmsm_power_down(M1_PM_COLD_CONFIG, true);
		return; /* We should never actually get here */
	}

	brcmstb_do_pmsm_power_down(PM_COLD_CONFIG, false);
}