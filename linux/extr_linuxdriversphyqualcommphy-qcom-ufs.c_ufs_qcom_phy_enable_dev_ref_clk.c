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
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ufs_qcom_phy_dev_ref_clk_ctrl (struct phy*,int) ; 

void ufs_qcom_phy_enable_dev_ref_clk(struct phy *generic_phy)
{
	ufs_qcom_phy_dev_ref_clk_ctrl(generic_phy, true);
}