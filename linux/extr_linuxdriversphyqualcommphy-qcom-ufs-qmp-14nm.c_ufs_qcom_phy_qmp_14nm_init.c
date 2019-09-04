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
struct ufs_qcom_phy {scalar_t__ mode; int is_started; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 scalar_t__ PHY_MODE_UFS_HS_B ; 
 struct ufs_qcom_phy* get_ufs_qcom_phy (struct phy*) ; 
 int ufs_qcom_phy_qmp_14nm_phy_calibrate (struct ufs_qcom_phy*,int) ; 

__attribute__((used)) static int ufs_qcom_phy_qmp_14nm_init(struct phy *generic_phy)
{
	struct ufs_qcom_phy *phy_common = get_ufs_qcom_phy(generic_phy);
	bool is_rate_B = false;
	int ret;

	if (phy_common->mode == PHY_MODE_UFS_HS_B)
		is_rate_B = true;

	ret = ufs_qcom_phy_qmp_14nm_phy_calibrate(phy_common, is_rate_B);
	if (!ret)
		/* phy calibrated, but yet to be started */
		phy_common->is_started = false;

	return ret;
}