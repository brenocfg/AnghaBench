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
struct phy_dm_struct {int support_ic_type; } ;
typedef  enum odm_bw { ____Placeholder_odm_bw } odm_bw ;

/* Variables and functions */
 int ODM_RTL8822B ; 
 int config_phydm_switch_channel_bw_8822b (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool phydm_api_switch_bw_channel(struct phy_dm_struct *dm, u8 central_ch,
					u8 primary_ch_idx,
					enum odm_bw bandwidth)
{
	bool ret = false;

	if (dm->support_ic_type & ODM_RTL8822B)
		ret = config_phydm_switch_channel_bw_8822b(
			dm, central_ch, primary_ch_idx, bandwidth);

	return ret;
}