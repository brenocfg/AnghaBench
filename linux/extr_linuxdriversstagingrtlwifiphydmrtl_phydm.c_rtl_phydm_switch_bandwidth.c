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
struct rtl_priv {int dummy; } ;
struct phy_dm_struct {int dummy; } ;
typedef  enum odm_bw { ____Placeholder_odm_bw } odm_bw ;
typedef  enum ht_channel_width { ____Placeholder_ht_channel_width } ht_channel_width ;

/* Variables and functions */
 scalar_t__ IS_HARDWARE_TYPE_8822B (struct rtl_priv*) ; 
 int config_phydm_switch_bandwidth_8822b (struct phy_dm_struct*,int /*<<< orphan*/ ,int) ; 
 struct phy_dm_struct* rtlpriv_to_phydm (struct rtl_priv*) ; 

__attribute__((used)) static bool rtl_phydm_switch_bandwidth(struct rtl_priv *rtlpriv,
				       u8 primary_ch_idx,
				       enum ht_channel_width bandwidth)
{
	struct phy_dm_struct *dm = rtlpriv_to_phydm(rtlpriv);
	enum odm_bw odm_bw = (enum odm_bw)bandwidth;

	if (IS_HARDWARE_TYPE_8822B(rtlpriv))
		return config_phydm_switch_bandwidth_8822b(dm, primary_ch_idx,
							   odm_bw);

	return false;
}