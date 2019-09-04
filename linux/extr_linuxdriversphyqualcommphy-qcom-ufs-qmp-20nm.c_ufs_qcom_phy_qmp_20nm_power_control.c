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
struct ufs_qcom_phy {int quirks; scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ QSERDES_COM_SYSCLK_EN_SEL_TXBAND ; 
 scalar_t__ UFS_PHY_POWER_DOWN_CONTROL ; 
 int UFS_QCOM_PHY_QUIRK_HIBERN8_EXIT_AFTER_PHY_PWR_COLLAPSE ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static
void ufs_qcom_phy_qmp_20nm_power_control(struct ufs_qcom_phy *phy, bool val)
{
	bool hibern8_exit_after_pwr_collapse = phy->quirks &
		UFS_QCOM_PHY_QUIRK_HIBERN8_EXIT_AFTER_PHY_PWR_COLLAPSE;

	if (val) {
		writel_relaxed(0x1, phy->mmio + UFS_PHY_POWER_DOWN_CONTROL);
		/*
		 * Before any transactions involving PHY, ensure PHY knows
		 * that it's analog rail is powered ON.
		 */
		mb();

		if (hibern8_exit_after_pwr_collapse) {
			/*
			 * Give atleast 1us delay after restoring PHY analog
			 * power.
			 */
			usleep_range(1, 2);
			writel_relaxed(0x0A, phy->mmio +
				       QSERDES_COM_SYSCLK_EN_SEL_TXBAND);
			writel_relaxed(0x08, phy->mmio +
				       QSERDES_COM_SYSCLK_EN_SEL_TXBAND);
			/*
			 * Make sure workaround is deactivated before proceeding
			 * with normal PHY operations.
			 */
			mb();
		}
	} else {
		if (hibern8_exit_after_pwr_collapse) {
			writel_relaxed(0x0A, phy->mmio +
				       QSERDES_COM_SYSCLK_EN_SEL_TXBAND);
			writel_relaxed(0x02, phy->mmio +
				       QSERDES_COM_SYSCLK_EN_SEL_TXBAND);
			/*
			 * Make sure that above workaround is activated before
			 * PHY analog power collapse.
			 */
			mb();
		}

		writel_relaxed(0x0, phy->mmio + UFS_PHY_POWER_DOWN_CONTROL);
		/*
		 * ensure that PHY knows its PHY analog rail is going
		 * to be powered down
		 */
		mb();
	}
}