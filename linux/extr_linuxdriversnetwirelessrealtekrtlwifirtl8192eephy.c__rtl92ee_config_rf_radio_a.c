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
typedef  int u32 ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  _rtl92ee_config_rf_reg (struct ieee80211_hw*,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl92ee_config_rf_radio_a(struct ieee80211_hw *hw,
				       u32 addr, u32 data)
{
	u32 content = 0x1000; /*RF Content: radio_a_txt*/
	u32 maskforphyset = (u32)(content & 0xE000);

	_rtl92ee_config_rf_reg(hw, addr, data, RF90_PATH_A,
			       addr | maskforphyset);
}