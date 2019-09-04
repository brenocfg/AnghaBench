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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {int /*<<< orphan*/  hlid; } ;
struct TYPE_3__ {int /*<<< orphan*/  bcast_hlid; } ;
struct wl12xx_vif {scalar_t__ bss_type; TYPE_2__ sta; TYPE_1__ ap; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_AP_BSS ; 
 int /*<<< orphan*/  DEBUG_CRYPT ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int) ; 
 int wl12xx_cmd_set_default_wep_key (struct wl1271*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl1271_set_default_wep_key(struct wl1271 *wl,
				      struct wl12xx_vif *wlvif, u8 id)
{
	int ret;
	bool is_ap = (wlvif->bss_type == BSS_TYPE_AP_BSS);

	if (is_ap)
		ret = wl12xx_cmd_set_default_wep_key(wl, id,
						     wlvif->ap.bcast_hlid);
	else
		ret = wl12xx_cmd_set_default_wep_key(wl, id, wlvif->sta.hlid);

	if (ret < 0)
		return ret;

	wl1271_debug(DEBUG_CRYPT, "default wep key idx: %d", (int)id);
	return 0;
}