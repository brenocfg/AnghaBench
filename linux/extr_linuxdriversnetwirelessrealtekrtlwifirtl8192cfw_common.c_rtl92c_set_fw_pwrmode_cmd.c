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
typedef  int /*<<< orphan*/  u8 ;
struct rtl_ps_ctl {int smart_ps; int /*<<< orphan*/  reg_max_lps_awakeintvl; } ;
struct TYPE_2__ {scalar_t__ p2p; } ;
struct rtl_priv {TYPE_1__ mac80211; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  H2C_SETPWRMODE ; 
 int /*<<< orphan*/  RT_PRINT_DATA (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_H2CCMD_PWRMODE_PARM_BCN_PASS_TIME (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_H2CCMD_PWRMODE_PARM_MODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_H2CCMD_PWRMODE_PARM_SMART_PS (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtl92c_fill_h2c_cmd (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 

void rtl92c_set_fw_pwrmode_cmd(struct ieee80211_hw *hw, u8 mode)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 u1_h2c_set_pwrmode[3] = { 0 };
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD, "FW LPS mode = %d\n", mode);

	SET_H2CCMD_PWRMODE_PARM_MODE(u1_h2c_set_pwrmode, mode);
	SET_H2CCMD_PWRMODE_PARM_SMART_PS(u1_h2c_set_pwrmode,
		(rtlpriv->mac80211.p2p) ? ppsc->smart_ps : 1);
	SET_H2CCMD_PWRMODE_PARM_BCN_PASS_TIME(u1_h2c_set_pwrmode,
					      ppsc->reg_max_lps_awakeintvl);

	RT_PRINT_DATA(rtlpriv, COMP_CMD, DBG_DMESG,
		      "rtl92c_set_fw_rsvdpagepkt(): u1_h2c_set_pwrmode\n",
		      u1_h2c_set_pwrmode, 3);
	rtl92c_fill_h2c_cmd(hw, H2C_SETPWRMODE, 3, u1_h2c_set_pwrmode);
}