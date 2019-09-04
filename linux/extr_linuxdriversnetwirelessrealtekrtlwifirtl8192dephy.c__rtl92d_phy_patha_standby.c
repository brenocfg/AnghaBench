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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FINIT ; 
 int /*<<< orphan*/  INIT_IQK ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int RFPGA0_XA_LSSIPARAMETER ; 
 int /*<<< orphan*/  RTPRINT (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl92d_phy_patha_standby(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Path-A standby mode!\n");

	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x0);
	rtl_set_bbreg(hw, RFPGA0_XA_LSSIPARAMETER, MASKDWORD, 0x00010000);
	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x80800000);
}