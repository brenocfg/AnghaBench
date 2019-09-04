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
struct wl1251 {int mac80211_registered; int /*<<< orphan*/  hw; int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ieee80211_register_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_error (char*,int) ; 
 int /*<<< orphan*/  wl1251_notice (char*) ; 

__attribute__((used)) static int wl1251_register_hw(struct wl1251 *wl)
{
	int ret;

	if (wl->mac80211_registered)
		return 0;

	SET_IEEE80211_PERM_ADDR(wl->hw, wl->mac_addr);

	ret = ieee80211_register_hw(wl->hw);
	if (ret < 0) {
		wl1251_error("unable to register mac80211 hw: %d", ret);
		return ret;
	}

	wl->mac80211_registered = true;

	wl1251_notice("loaded");

	return 0;
}