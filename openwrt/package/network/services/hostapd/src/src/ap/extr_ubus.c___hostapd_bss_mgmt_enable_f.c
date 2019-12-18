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
typedef  int uint32_t ;
typedef  int u8 ;
struct hostapd_data {struct hostapd_bss_config* conf; } ;
struct hostapd_bss_config {int* radio_measurements; int bss_transition; } ;

/* Variables and functions */
#define  BSS_MGMT_EN_BEACON 130 
#define  BSS_MGMT_EN_BSS_TRANSITION 129 
#define  BSS_MGMT_EN_NEIGHBOR 128 
 int WLAN_RRM_CAPS_BEACON_REPORT_ACTIVE ; 
 int WLAN_RRM_CAPS_BEACON_REPORT_PASSIVE ; 
 int WLAN_RRM_CAPS_BEACON_REPORT_TABLE ; 
 int WLAN_RRM_CAPS_NEIGHBOR_REPORT ; 
 int /*<<< orphan*/  hostapd_neighbor_set_own_report (struct hostapd_data*) ; 

__attribute__((used)) static bool
__hostapd_bss_mgmt_enable_f(struct hostapd_data *hapd, int flag)
{
	struct hostapd_bss_config *bss = hapd->conf;
	uint32_t flags;

	switch (flag) {
	case BSS_MGMT_EN_NEIGHBOR:
		if (bss->radio_measurements[0] &
		    WLAN_RRM_CAPS_NEIGHBOR_REPORT)
			return false;

		bss->radio_measurements[0] |=
			WLAN_RRM_CAPS_NEIGHBOR_REPORT;
		hostapd_neighbor_set_own_report(hapd);
		return true;
	case BSS_MGMT_EN_BEACON:
		flags = WLAN_RRM_CAPS_BEACON_REPORT_PASSIVE |
			WLAN_RRM_CAPS_BEACON_REPORT_ACTIVE |
			WLAN_RRM_CAPS_BEACON_REPORT_TABLE;

		if (bss->radio_measurements[0] & flags == flags)
			return false;

		bss->radio_measurements[0] |= (u8) flags;
		return true;
#ifdef CONFIG_WNM_AP
	case BSS_MGMT_EN_BSS_TRANSITION:
		if (bss->bss_transition)
			return false;

		bss->bss_transition = 1;
		return true;
#endif
	}
}