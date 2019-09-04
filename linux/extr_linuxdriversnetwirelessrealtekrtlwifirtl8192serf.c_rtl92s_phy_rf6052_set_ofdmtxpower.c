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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl92s_get_powerbase (struct ieee80211_hw*,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  _rtl92s_get_txpower_writeval_byregulatory (struct ieee80211_hw*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtl92s_set_antennadiff (struct ieee80211_hw*,int*) ; 
 int /*<<< orphan*/  _rtl92s_write_ofdm_powerreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ) ; 

void rtl92s_phy_rf6052_set_ofdmtxpower(struct ieee80211_hw *hw,
				       u8 *p_pwrlevel, u8 chnl)
{
	u32 writeval, pwrbase0, pwrbase1;
	u8 index = 0;
	u8 finalpwr_idx[4];

	_rtl92s_get_powerbase(hw, p_pwrlevel, chnl, &pwrbase0, &pwrbase1,
			&finalpwr_idx[0]);
	_rtl92s_set_antennadiff(hw, &finalpwr_idx[0]);

	for (index = 0; index < 6; index++) {
		_rtl92s_get_txpower_writeval_byregulatory(hw, chnl, index,
				pwrbase0, pwrbase1, &writeval);

		_rtl92s_write_ofdm_powerreg(hw, index, writeval);
	}
}