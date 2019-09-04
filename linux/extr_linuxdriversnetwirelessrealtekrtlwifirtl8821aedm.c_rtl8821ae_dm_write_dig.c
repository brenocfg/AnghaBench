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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ rf_type; } ;
struct dig_t {scalar_t__ cur_igvalue; scalar_t__ stop_dig; } ;
struct rtl_priv {TYPE_1__ phy; struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_BIT_IGI_11AC ; 
 int /*<<< orphan*/  DM_REG_IGI_A_11AC ; 
 int /*<<< orphan*/  DM_REG_IGI_B_11AC ; 
 scalar_t__ RF_1T1R ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void rtl8821ae_dm_write_dig(struct ieee80211_hw *hw, u8 current_igi)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_digtable = &rtlpriv->dm_digtable;

	if (dm_digtable->stop_dig)
		return;

	if (dm_digtable->cur_igvalue != current_igi) {
		rtl_set_bbreg(hw, DM_REG_IGI_A_11AC,
			      DM_BIT_IGI_11AC, current_igi);
		if (rtlpriv->phy.rf_type != RF_1T1R)
			rtl_set_bbreg(hw, DM_REG_IGI_B_11AC,
				      DM_BIT_IGI_11AC, current_igi);
	}
	dm_digtable->cur_igvalue = current_igi;
}