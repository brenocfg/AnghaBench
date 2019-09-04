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
struct phy_dm_struct {int dummy; } ;
typedef  enum odm_bw { ____Placeholder_odm_bw } odm_bw ;

/* Variables and functions */
 int /*<<< orphan*/  config_phydm_switch_band_8822b (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_phydm_switch_bandwidth_8822b (struct phy_dm_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  config_phydm_switch_channel_8822b (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 

bool config_phydm_switch_channel_bw_8822b(struct phy_dm_struct *dm,
					  u8 central_ch, u8 primary_ch_idx,
					  enum odm_bw bandwidth)
{
	/* Switch band */
	if (!config_phydm_switch_band_8822b(dm, central_ch))
		return false;

	/* Switch channel */
	if (!config_phydm_switch_channel_8822b(dm, central_ch))
		return false;

	/* Switch bandwidth */
	if (!config_phydm_switch_bandwidth_8822b(dm, primary_ch_idx, bandwidth))
		return false;

	return true;
}