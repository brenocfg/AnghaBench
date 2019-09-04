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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u16 ;
struct ufs_qcom_phy {void* host_ctrl_rev_step; void* host_ctrl_rev_minor; int /*<<< orphan*/  host_ctrl_rev_major; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 struct ufs_qcom_phy* get_ufs_qcom_phy (struct phy*) ; 

void ufs_qcom_phy_save_controller_version(struct phy *generic_phy,
					  u8 major, u16 minor, u16 step)
{
	struct ufs_qcom_phy *ufs_qcom_phy = get_ufs_qcom_phy(generic_phy);

	ufs_qcom_phy->host_ctrl_rev_major = major;
	ufs_qcom_phy->host_ctrl_rev_minor = minor;
	ufs_qcom_phy->host_ctrl_rev_step = step;
}