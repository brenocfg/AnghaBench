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
struct wl12xx_vif {int ba_allowed; scalar_t__ bss_type; int ba_support; } ;
struct wl1271 {scalar_t__ ba_rx_session_count; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_AP_BSS ; 
 scalar_t__ BSS_TYPE_STA_BSS ; 
 int wl12xx_acx_set_ba_initiator_policy (struct wl1271*,struct wl12xx_vif*) ; 

__attribute__((used)) static int wl1271_set_ba_policies(struct wl1271 *wl, struct wl12xx_vif *wlvif)
{
	/* Reset the BA RX indicators */
	wlvif->ba_allowed = true;
	wl->ba_rx_session_count = 0;

	/* BA is supported in STA/AP modes */
	if (wlvif->bss_type != BSS_TYPE_AP_BSS &&
	    wlvif->bss_type != BSS_TYPE_STA_BSS) {
		wlvif->ba_support = false;
		return 0;
	}

	wlvif->ba_support = true;

	/* 802.11n initiator BA session setting */
	return wl12xx_acx_set_ba_initiator_policy(wl, wlvif);
}