#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct TYPE_2__ {scalar_t__ index; int full; int /*<<< orphan*/ * samples; } ;
struct network_info {int found; void* join_params; void* time_scan_cached; void* time_scan; scalar_t__ ies_len; void* ies; int /*<<< orphan*/  tsf_hi; int /*<<< orphan*/  ch; int /*<<< orphan*/  dtim_period; int /*<<< orphan*/  beacon_period; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  cap_info; int /*<<< orphan*/  rssi; TYPE_1__ rssi_history; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MAX_NUM_SCANNED_NETWORKS_SHADOW ; 
 scalar_t__ NUM_RSSI ; 
 int is_network_in_shadow (struct network_info*,void*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ last_scanned_cnt ; 
 struct network_info* last_scanned_shadow ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_network_to_shadow(struct network_info *nw_info,
				  void *user_void, void *join_params)
{
	int ap_found = is_network_in_shadow(nw_info, user_void);
	u32 ap_index = 0;
	u8 rssi_index = 0;
	struct network_info *shadow_nw_info;

	if (last_scanned_cnt >= MAX_NUM_SCANNED_NETWORKS_SHADOW)
		return;

	if (ap_found == -1) {
		ap_index = last_scanned_cnt;
		last_scanned_cnt++;
	} else {
		ap_index = ap_found;
	}
	shadow_nw_info = &last_scanned_shadow[ap_index];
	rssi_index = shadow_nw_info->rssi_history.index;
	shadow_nw_info->rssi_history.samples[rssi_index++] = nw_info->rssi;
	if (rssi_index == NUM_RSSI) {
		rssi_index = 0;
		shadow_nw_info->rssi_history.full = true;
	}
	shadow_nw_info->rssi_history.index = rssi_index;
	shadow_nw_info->rssi = nw_info->rssi;
	shadow_nw_info->cap_info = nw_info->cap_info;
	shadow_nw_info->ssid_len = nw_info->ssid_len;
	memcpy(shadow_nw_info->ssid, nw_info->ssid, nw_info->ssid_len);
	memcpy(shadow_nw_info->bssid, nw_info->bssid, ETH_ALEN);
	shadow_nw_info->beacon_period = nw_info->beacon_period;
	shadow_nw_info->dtim_period = nw_info->dtim_period;
	shadow_nw_info->ch = nw_info->ch;
	shadow_nw_info->tsf_hi = nw_info->tsf_hi;
	if (ap_found != -1)
		kfree(shadow_nw_info->ies);
	shadow_nw_info->ies = kmemdup(nw_info->ies, nw_info->ies_len,
				      GFP_KERNEL);
	if (shadow_nw_info->ies)
		shadow_nw_info->ies_len = nw_info->ies_len;
	else
		shadow_nw_info->ies_len = 0;
	shadow_nw_info->time_scan = jiffies;
	shadow_nw_info->time_scan_cached = jiffies;
	shadow_nw_info->found = 1;
	if (ap_found != -1)
		kfree(shadow_nw_info->join_params);
	shadow_nw_info->join_params = join_params;
}