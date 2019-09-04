#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_4__ {int version; } ;
struct rtl_priv {TYPE_2__ rtlhal; TYPE_1__* intf_ops; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum version_8192d { ____Placeholder_version_8192d } version_8192d ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_efuse_byte ) (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int CHIP_92D_C_CUT ; 
 int CHIP_92D_D_CUT ; 
 int CHIP_92D_E_CUT ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  EEPROME_CHIP_VERSION_H ; 
 int /*<<< orphan*/  EEPROME_CHIP_VERSION_L ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void _rtl92de_efuse_update_chip_version(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	enum version_8192d chipver = rtlpriv->rtlhal.version;
	u8 cutvalue[2];
	u16 chipvalue;

	rtlpriv->intf_ops->read_efuse_byte(hw, EEPROME_CHIP_VERSION_H,
					   &cutvalue[1]);
	rtlpriv->intf_ops->read_efuse_byte(hw, EEPROME_CHIP_VERSION_L,
					   &cutvalue[0]);
	chipvalue = (cutvalue[1] << 8) | cutvalue[0];
	switch (chipvalue) {
	case 0xAA55:
		chipver |= CHIP_92D_C_CUT;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "C-CUT!!!\n");
		break;
	case 0x9966:
		chipver |= CHIP_92D_D_CUT;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "D-CUT!!!\n");
		break;
	case 0xCC33:
		chipver |= CHIP_92D_E_CUT;
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "E-CUT!!!\n");
		break;
	default:
		chipver |= CHIP_92D_D_CUT;
		pr_err("Unknown CUT!\n");
		break;
	}
	rtlpriv->rtlhal.version = chipver;
}