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
struct ufs_qcom_host {int /*<<< orphan*/  generic_phy; } ;
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufs_qcom_disable_lane_clks (struct ufs_qcom_host*) ; 
 struct ufs_qcom_host* ufshcd_get_variant (struct ufs_hba*) ; 

__attribute__((used)) static void ufs_qcom_exit(struct ufs_hba *hba)
{
	struct ufs_qcom_host *host = ufshcd_get_variant(hba);

	ufs_qcom_disable_lane_clks(host);
	phy_power_off(host->generic_phy);
	phy_exit(host->generic_phy);
}