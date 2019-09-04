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
struct wl1251 {scalar_t__ station_mode; int /*<<< orphan*/  elp_work; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELP_ENTRY_DELAY ; 
 scalar_t__ STATION_ACTIVE_MODE ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 

void wl1251_ps_elp_sleep(struct wl1251 *wl)
{
	unsigned long delay;

	if (wl->station_mode != STATION_ACTIVE_MODE) {
		delay = msecs_to_jiffies(ELP_ENTRY_DELAY);
		ieee80211_queue_delayed_work(wl->hw, &wl->elp_work, delay);
	}
}