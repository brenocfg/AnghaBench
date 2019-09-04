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
typedef  scalar_t__ u8 ;
struct ieee80211_hw {int dummy; } ;
typedef  enum wireless_mode { ____Placeholder_wireless_mode } wireless_mode ;

/* Variables and functions */
 scalar_t__ MAX_TXPWR_IDX_NMODE_92S ; 
#define  WIRELESS_MODE_B 130 
#define  WIRELESS_MODE_G 129 
#define  WIRELESS_MODE_N_24G 128 

u8 _rtl92c_phy_dbm_to_txpwr_idx(struct ieee80211_hw *hw,
				enum wireless_mode wirelessmode,
				long power_indbm)
{
	u8 txpwridx;
	long offset;

	switch (wirelessmode) {
	case WIRELESS_MODE_B:
		offset = -7;
		break;
	case WIRELESS_MODE_G:
	case WIRELESS_MODE_N_24G:
		offset = -8;
		break;
	default:
		offset = -8;
		break;
	}

	if ((power_indbm - offset) > 0)
		txpwridx = (u8)((power_indbm - offset) * 2);
	else
		txpwridx = 0;

	if (txpwridx > MAX_TXPWR_IDX_NMODE_92S)
		txpwridx = MAX_TXPWR_IDX_NMODE_92S;

	return txpwridx;
}