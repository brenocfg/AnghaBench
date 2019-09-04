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
struct wl1271 {int event_mask; int /*<<< orphan*/  ap_event_mask; } ;

/* Variables and functions */
 int BA_SESSION_RX_CONSTRAINT_EVENT_ID ; 
 int BSS_LOSS_EVENT_ID ; 
 int CHANNEL_SWITCH_COMPLETE_EVENT_ID ; 
 int DFS_CHANNELS_CONFIG_COMPLETE_EVENT ; 
 int DUMMY_PACKET_EVENT_ID ; 
 int FW_LOGGER_INDICATION ; 
 int INACTIVE_STA_EVENT_ID ; 
 int /*<<< orphan*/  MAX_TX_FAILURE_EVENT_ID ; 
 int PEER_REMOVE_COMPLETE_EVENT_ID ; 
 int PERIODIC_SCAN_COMPLETE_EVENT_ID ; 
 int PERIODIC_SCAN_REPORT_EVENT_ID ; 
 int RADAR_DETECTED_EVENT_ID ; 
 int REMAIN_ON_CHANNEL_COMPLETE_EVENT_ID ; 
 int RSSI_SNR_TRIGGER_0_EVENT_ID ; 
 int RX_BA_WIN_SIZE_CHANGE_EVENT_ID ; 
 int SCAN_COMPLETE_EVENT_ID ; 
 int SMART_CONFIG_DECODE_EVENT_ID ; 
 int SMART_CONFIG_SYNC_EVENT_ID ; 
 int TIME_SYNC_EVENT_ID ; 
 int wl18xx_enable_interrupts (struct wl1271*) ; 
 int wl18xx_pre_boot (struct wl1271*) ; 
 int wl18xx_pre_upload (struct wl1271*) ; 
 int wl18xx_set_mac_and_phy (struct wl1271*) ; 
 int wlcore_boot_run_firmware (struct wl1271*) ; 
 int wlcore_boot_upload_firmware (struct wl1271*) ; 

__attribute__((used)) static int wl18xx_boot(struct wl1271 *wl)
{
	int ret;

	ret = wl18xx_pre_boot(wl);
	if (ret < 0)
		goto out;

	ret = wl18xx_pre_upload(wl);
	if (ret < 0)
		goto out;

	ret = wlcore_boot_upload_firmware(wl);
	if (ret < 0)
		goto out;

	ret = wl18xx_set_mac_and_phy(wl);
	if (ret < 0)
		goto out;

	wl->event_mask = BSS_LOSS_EVENT_ID |
		SCAN_COMPLETE_EVENT_ID |
		RADAR_DETECTED_EVENT_ID |
		RSSI_SNR_TRIGGER_0_EVENT_ID |
		PERIODIC_SCAN_COMPLETE_EVENT_ID |
		PERIODIC_SCAN_REPORT_EVENT_ID |
		DUMMY_PACKET_EVENT_ID |
		PEER_REMOVE_COMPLETE_EVENT_ID |
		BA_SESSION_RX_CONSTRAINT_EVENT_ID |
		REMAIN_ON_CHANNEL_COMPLETE_EVENT_ID |
		INACTIVE_STA_EVENT_ID |
		CHANNEL_SWITCH_COMPLETE_EVENT_ID |
		DFS_CHANNELS_CONFIG_COMPLETE_EVENT |
		SMART_CONFIG_SYNC_EVENT_ID |
		SMART_CONFIG_DECODE_EVENT_ID |
		TIME_SYNC_EVENT_ID |
		FW_LOGGER_INDICATION |
		RX_BA_WIN_SIZE_CHANGE_EVENT_ID;

	wl->ap_event_mask = MAX_TX_FAILURE_EVENT_ID;

	ret = wlcore_boot_run_firmware(wl);
	if (ret < 0)
		goto out;

	ret = wl18xx_enable_interrupts(wl);

out:
	return ret;
}