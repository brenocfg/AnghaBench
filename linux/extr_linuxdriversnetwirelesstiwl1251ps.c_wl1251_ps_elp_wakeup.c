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
struct wl1251 {int elp; int /*<<< orphan*/  elp_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PSM ; 
 int /*<<< orphan*/  ELPCTRL_WAKE_UP ; 
 int ELPCTRL_WLAN_READY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HW_ACCESS_ELP_CTRL_REG_ADDR ; 
 int /*<<< orphan*/  WL1251_WAKEUP_TIMEOUT ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wl1251_error (char*) ; 
 int wl1251_read_elp (struct wl1251*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_write_elp (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wl1251_ps_elp_wakeup(struct wl1251 *wl)
{
	unsigned long timeout, start;
	u32 elp_reg;

	cancel_delayed_work(&wl->elp_work);

	if (!wl->elp)
		return 0;

	wl1251_debug(DEBUG_PSM, "waking up chip from elp");

	start = jiffies;
	timeout = jiffies + msecs_to_jiffies(WL1251_WAKEUP_TIMEOUT);

	wl1251_write_elp(wl, HW_ACCESS_ELP_CTRL_REG_ADDR, ELPCTRL_WAKE_UP);

	elp_reg = wl1251_read_elp(wl, HW_ACCESS_ELP_CTRL_REG_ADDR);

	/*
	 * FIXME: we should wait for irq from chip but, as a temporary
	 * solution to simplify locking, let's poll instead
	 */
	while (!(elp_reg & ELPCTRL_WLAN_READY)) {
		if (time_after(jiffies, timeout)) {
			wl1251_error("elp wakeup timeout");
			return -ETIMEDOUT;
		}
		msleep(1);
		elp_reg = wl1251_read_elp(wl, HW_ACCESS_ELP_CTRL_REG_ADDR);
	}

	wl1251_debug(DEBUG_PSM, "wakeup time: %u ms",
		     jiffies_to_msecs(jiffies - start));

	wl->elp = false;

	return 0;
}