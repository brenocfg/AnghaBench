#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sta_hlid_map; } ;
struct wl12xx_vif {TYPE_1__ ap; } ;
struct wl1271_station {size_t hlid; int /*<<< orphan*/  total_freed_pkts; } ;
struct wl1271 {scalar_t__ active_sta_count; scalar_t__ max_ap_stations; TYPE_2__* links; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  total_freed_pkts; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 
 int wl12xx_allocate_link (struct wl1271*,struct wl12xx_vif*,size_t*) ; 

__attribute__((used)) static int wl1271_allocate_sta(struct wl1271 *wl,
			     struct wl12xx_vif *wlvif,
			     struct ieee80211_sta *sta)
{
	struct wl1271_station *wl_sta;
	int ret;


	if (wl->active_sta_count >= wl->max_ap_stations) {
		wl1271_warning("could not allocate HLID - too much stations");
		return -EBUSY;
	}

	wl_sta = (struct wl1271_station *)sta->drv_priv;
	ret = wl12xx_allocate_link(wl, wlvif, &wl_sta->hlid);
	if (ret < 0) {
		wl1271_warning("could not allocate HLID - too many links");
		return -EBUSY;
	}

	/* use the previous security seq, if this is a recovery/resume */
	wl->links[wl_sta->hlid].total_freed_pkts = wl_sta->total_freed_pkts;

	set_bit(wl_sta->hlid, wlvif->ap.sta_hlid_map);
	memcpy(wl->links[wl_sta->hlid].addr, sta->addr, ETH_ALEN);
	wl->active_sta_count++;
	return 0;
}