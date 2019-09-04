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
struct wl1251 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_REG_SLV_SOFT_RESET ; 
 int ACX_SLV_SOFT_RESET_BIT ; 
 int /*<<< orphan*/  DEBUG_BOOT ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  SOFT_RESET_MAX_TIME ; 
 int /*<<< orphan*/  SOFT_RESET_STALL_TIME ; 
 int /*<<< orphan*/  SPARE_A2 ; 
 unsigned long jiffies ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 unsigned long usecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wl1251_error (char*) ; 
 int wl1251_reg_read32 (struct wl1251*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_reg_write32 (struct wl1251*,int /*<<< orphan*/ ,int) ; 

int wl1251_boot_soft_reset(struct wl1251 *wl)
{
	unsigned long timeout;
	u32 boot_data;

	/* perform soft reset */
	wl1251_reg_write32(wl, ACX_REG_SLV_SOFT_RESET, ACX_SLV_SOFT_RESET_BIT);

	/* SOFT_RESET is self clearing */
	timeout = jiffies + usecs_to_jiffies(SOFT_RESET_MAX_TIME);
	while (1) {
		boot_data = wl1251_reg_read32(wl, ACX_REG_SLV_SOFT_RESET);
		wl1251_debug(DEBUG_BOOT, "soft reset bootdata 0x%x", boot_data);
		if ((boot_data & ACX_SLV_SOFT_RESET_BIT) == 0)
			break;

		if (time_after(jiffies, timeout)) {
			/* 1.2 check pWhalBus->uSelfClearTime if the
			 * timeout was reached */
			wl1251_error("soft reset timeout");
			return -1;
		}

		udelay(SOFT_RESET_STALL_TIME);
	}

	/* disable Rx/Tx */
	wl1251_reg_write32(wl, ENABLE, 0x0);

	/* disable auto calibration on start*/
	wl1251_reg_write32(wl, SPARE_A2, 0xffff);

	return 0;
}