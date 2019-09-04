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
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2C_92E_P2P_PS_CTW_CMD ; 
 int /*<<< orphan*/  rtl92ee_fill_h2c_cmd (struct ieee80211_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl92ee_set_p2p_ctw_period_cmd(struct ieee80211_hw *hw, u8 ctwindow)
{
	u8 u1_ctwindow_period[1] = {ctwindow};

	rtl92ee_fill_h2c_cmd(hw, H2C_92E_P2P_PS_CTW_CMD, 1, u1_ctwindow_period);
}