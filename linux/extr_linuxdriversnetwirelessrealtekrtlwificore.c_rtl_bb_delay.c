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
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  rtl_addr_delay (int) ; 
 int /*<<< orphan*/  rtl_set_bbreg (struct ieee80211_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void rtl_bb_delay(struct ieee80211_hw *hw, u32 addr, u32 data)
{
	if (addr >= 0xf9 && addr <= 0xfe) {
		rtl_addr_delay(addr);
	} else {
		rtl_set_bbreg(hw, addr, MASKDWORD, data);
		udelay(1);
	}
}