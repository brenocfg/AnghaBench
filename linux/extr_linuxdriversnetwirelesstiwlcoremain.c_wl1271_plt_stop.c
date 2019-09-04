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
struct wl1271 {int plt; int /*<<< orphan*/  mutex; scalar_t__ rx_counter; int /*<<< orphan*/  plt_mode; int /*<<< orphan*/  state; int /*<<< orphan*/  sleep_auth; scalar_t__ flags; int /*<<< orphan*/  tx_watchdog_work; int /*<<< orphan*/  recovery_work; int /*<<< orphan*/  netstack_work; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  PLT_OFF ; 
 int /*<<< orphan*/  WL1271_PSM_ILLEGAL ; 
 int /*<<< orphan*/  WLCORE_STATE_OFF ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_flush_deferred_work (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_notice (char*) ; 
 int /*<<< orphan*/  wl1271_power_off (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_disable_interrupts (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_enable_interrupts (struct wl1271*) ; 

int wl1271_plt_stop(struct wl1271 *wl)
{
	int ret = 0;

	wl1271_notice("power down");

	/*
	 * Interrupts must be disabled before setting the state to OFF.
	 * Otherwise, the interrupt handler might be called and exit without
	 * reading the interrupt status.
	 */
	wlcore_disable_interrupts(wl);
	mutex_lock(&wl->mutex);
	if (!wl->plt) {
		mutex_unlock(&wl->mutex);

		/*
		 * This will not necessarily enable interrupts as interrupts
		 * may have been disabled when op_stop was called. It will,
		 * however, balance the above call to disable_interrupts().
		 */
		wlcore_enable_interrupts(wl);

		wl1271_error("cannot power down because not in PLT "
			     "state: %d", wl->state);
		ret = -EBUSY;
		goto out;
	}

	mutex_unlock(&wl->mutex);

	wl1271_flush_deferred_work(wl);
	cancel_work_sync(&wl->netstack_work);
	cancel_work_sync(&wl->recovery_work);
	cancel_delayed_work_sync(&wl->tx_watchdog_work);

	mutex_lock(&wl->mutex);
	wl1271_power_off(wl);
	wl->flags = 0;
	wl->sleep_auth = WL1271_PSM_ILLEGAL;
	wl->state = WLCORE_STATE_OFF;
	wl->plt = false;
	wl->plt_mode = PLT_OFF;
	wl->rx_counter = 0;
	mutex_unlock(&wl->mutex);

out:
	return ret;
}