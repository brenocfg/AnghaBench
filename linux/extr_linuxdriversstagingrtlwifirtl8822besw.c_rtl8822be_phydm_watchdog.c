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
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct rtl_priv {TYPE_2__ phydm; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* phydm_watchdog ) (struct rtl_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct rtl_priv*) ; 

__attribute__((used)) static void rtl8822be_phydm_watchdog(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u32 tmp;

	tmp = rtl_read_dword(rtlpriv, 0xc00);
	if (tmp & 0xFF000000) { /* Recover 0xC00: 0xF800000C --> 0x0000000C */
		RT_TRACE(rtlpriv, COMP_RF, DBG_DMESG,
			 "found regaddr_c00=%08X\n", tmp);
		tmp &= ~0xFF000000;
		rtl_write_dword(rtlpriv, 0xc00, tmp);
		RT_TRACE(rtlpriv, COMP_RF, DBG_DMESG,
			 "apply regaddr_c00=%08X\n", tmp);
	}

	rtlpriv->phydm.ops->phydm_watchdog(rtlpriv);
}