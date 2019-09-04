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
struct ufs_qcom_phy {int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 int /*<<< orphan*/  UFS_QCOM_PHY_QUIRK_HIBERN8_EXIT_AFTER_PHY_PWR_COLLAPSE ; 

__attribute__((used)) static
void ufs_qcom_phy_qmp_20nm_advertise_quirks(struct ufs_qcom_phy *phy_common)
{
	phy_common->quirks =
		UFS_QCOM_PHY_QUIRK_HIBERN8_EXIT_AFTER_PHY_PWR_COLLAPSE;
}