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
struct wl1271 {int mac80211_registered; int /*<<< orphan*/  hw; scalar_t__ plt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_unregister_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_plt_stop (struct wl1271*) ; 

__attribute__((used)) static void wl1271_unregister_hw(struct wl1271 *wl)
{
	if (wl->plt)
		wl1271_plt_stop(wl);

	ieee80211_unregister_hw(wl->hw);
	wl->mac80211_registered = false;

}