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
struct TYPE_2__ {int /*<<< orphan*/  dm_initialgain_enable; } ;
struct dig_t {int /*<<< orphan*/  dig_enable_flag; } ;
struct rtl_priv {TYPE_1__ dm; struct dig_t dm_digtable; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl8723e_dm_ctrl_initgain_by_twoport (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl8723e_dm_dig(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct dig_t *dm_digtable = &rtlpriv->dm_digtable;

	if (!rtlpriv->dm.dm_initialgain_enable)
		return;
	if (!dm_digtable->dig_enable_flag)
		return;

	rtl8723e_dm_ctrl_initgain_by_twoport(hw);

}