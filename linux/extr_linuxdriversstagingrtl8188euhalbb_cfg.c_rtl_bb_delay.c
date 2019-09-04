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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  phy_set_bb_reg (struct adapter*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rtl_bb_delay(struct adapter *adapt, u32 addr, u32 data)
{
	if (addr == 0xfe) {
		msleep(50);
	} else if (addr == 0xfd) {
		mdelay(5);
	} else if (addr == 0xfc) {
		mdelay(1);
	} else if (addr == 0xfb) {
		udelay(50);
	} else if (addr == 0xfa) {
		udelay(5);
	} else if (addr == 0xf9) {
		udelay(1);
	} else {
		phy_set_bb_reg(adapt, addr, bMaskDWord, data);
		/*  Add 1us delay between BB/RF register setting. */
		udelay(1);
	}
}