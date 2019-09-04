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
typedef  scalar_t__ u16 ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 scalar_t__ BPHY_RSSI_LUT ; 
 scalar_t__ BPHY_RSSI_LUT_END ; 
 scalar_t__ BPHY_STEP ; 
 scalar_t__ NPHY_TO_BPHY_OFF ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,scalar_t__,int) ; 

__attribute__((used)) static void wlc_phy_bphy_init_nphy(struct brcms_phy *pi)
{
	u16 addr, val;

	val = 0x1e1f;
	for (addr = (NPHY_TO_BPHY_OFF + BPHY_RSSI_LUT);
	     addr <= (NPHY_TO_BPHY_OFF + BPHY_RSSI_LUT_END); addr++) {
		write_phy_reg(pi, addr, val);
		if (addr == (NPHY_TO_BPHY_OFF + 0x97))
			val = 0x3e3f;
		else
			val -= 0x0202;
	}

	write_phy_reg(pi, NPHY_TO_BPHY_OFF + BPHY_STEP, 0x668);
}