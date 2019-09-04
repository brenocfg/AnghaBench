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
typedef  size_t u8 ;
typedef  int u32 ;
struct wl18xx_event_mailbox {int number_of_scan_results; int number_of_sched_scan_results; size_t rx_ba_link_id; size_t rx_ba_win_size; int /*<<< orphan*/  sc_pwd; int /*<<< orphan*/  sc_pwd_len; int /*<<< orphan*/  sc_ssid; int /*<<< orphan*/  sc_ssid_len; int /*<<< orphan*/  sc_sync_band; int /*<<< orphan*/  sc_sync_channel; int /*<<< orphan*/  inactive_sta_bitmap; int /*<<< orphan*/  tx_retry_exceeded_bitmap; int /*<<< orphan*/  channel_switch_role_id_bitmap; int /*<<< orphan*/  bss_loss_bitmap; int /*<<< orphan*/  rx_ba_allowed_bitmap; int /*<<< orphan*/  rx_ba_role_id_bitmap; int /*<<< orphan*/  rssi_snr_trigger_metric; int /*<<< orphan*/  radar_type; int /*<<< orphan*/  radar_channel; int /*<<< orphan*/  time_sync_tsf_low_lsb; int /*<<< orphan*/  time_sync_tsf_low_msb; int /*<<< orphan*/  time_sync_tsf_high_lsb; int /*<<< orphan*/  time_sync_tsf_high_msb; int /*<<< orphan*/  events_vector; } ;
struct wl12xx_vif {scalar_t__ bss_type; } ;
struct wl1271 {TYPE_2__* links; int /*<<< orphan*/  hw; int /*<<< orphan*/  radar_debug_mode; scalar_t__ scan_wlvif; struct wl18xx_event_mailbox* mbox; } ;
struct TYPE_3__ {size_t* bssid; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
struct ieee80211_sta {size_t max_rx_aggregation_subframes; } ;
struct TYPE_4__ {size_t* addr; int /*<<< orphan*/  ba_bitmap; struct wl12xx_vif* wlvif; } ;

/* Variables and functions */
 int BA_SESSION_RX_CONSTRAINT_EVENT_ID ; 
 int BSS_LOSS_EVENT_ID ; 
 scalar_t__ BSS_TYPE_AP_BSS ; 
 int CHANNEL_SWITCH_COMPLETE_EVENT_ID ; 
 int /*<<< orphan*/  DEBUG_EVENT ; 
 int DUMMY_PACKET_EVENT_ID ; 
 int FW_LOGGER_INDICATION ; 
 int INACTIVE_STA_EVENT_ID ; 
 int MAX_TX_FAILURE_EVENT_ID ; 
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
 struct ieee80211_sta* ieee80211_find_sta (struct ieee80211_vif*,size_t const*) ; 
 int /*<<< orphan*/  ieee80211_radar_detected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_stop_rx_ba_session (struct ieee80211_vif*,int /*<<< orphan*/ ,size_t const*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wl1271_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_vif* wl12xx_wlvif_to_vif (struct wl12xx_vif*) ; 
 int /*<<< orphan*/  wl18xx_radar_type_decode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl18xx_scan_completed (struct wl1271*,scalar_t__) ; 
 int /*<<< orphan*/  wlcore_event_ba_rx_constraint (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_event_beacon_loss (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_event_channel_switch (struct wl1271*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlcore_event_dummy_packet (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_event_fw_logger (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_event_inactive_sta (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_event_max_tx_failure (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_event_roc_complete (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_event_rssi_trigger (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_event_sched_scan_completed (struct wl1271*,int) ; 
 int /*<<< orphan*/  wlcore_event_time_sync (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_scan_sched_scan_results (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_smart_config_decode_event (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlcore_smart_config_sync_event (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wl18xx_process_mailbox_events(struct wl1271 *wl)
{
	struct wl18xx_event_mailbox *mbox = wl->mbox;
	u32 vector;

	vector = le32_to_cpu(mbox->events_vector);
	wl1271_debug(DEBUG_EVENT, "MBOX vector: 0x%x", vector);

	if (vector & SCAN_COMPLETE_EVENT_ID) {
		wl1271_debug(DEBUG_EVENT, "scan results: %d",
			     mbox->number_of_scan_results);

		if (wl->scan_wlvif)
			wl18xx_scan_completed(wl, wl->scan_wlvif);
	}

	if (vector & TIME_SYNC_EVENT_ID)
		wlcore_event_time_sync(wl,
			mbox->time_sync_tsf_high_msb,
			mbox->time_sync_tsf_high_lsb,
			mbox->time_sync_tsf_low_msb,
			mbox->time_sync_tsf_low_lsb);

	if (vector & RADAR_DETECTED_EVENT_ID) {
		wl1271_info("radar event: channel %d type %s",
			    mbox->radar_channel,
			    wl18xx_radar_type_decode(mbox->radar_type));

		if (!wl->radar_debug_mode)
			ieee80211_radar_detected(wl->hw);
	}

	if (vector & PERIODIC_SCAN_REPORT_EVENT_ID) {
		wl1271_debug(DEBUG_EVENT,
			     "PERIODIC_SCAN_REPORT_EVENT (results %d)",
			     mbox->number_of_sched_scan_results);

		wlcore_scan_sched_scan_results(wl);
	}

	if (vector & PERIODIC_SCAN_COMPLETE_EVENT_ID)
		wlcore_event_sched_scan_completed(wl, 1);

	if (vector & RSSI_SNR_TRIGGER_0_EVENT_ID)
		wlcore_event_rssi_trigger(wl, mbox->rssi_snr_trigger_metric);

	if (vector & BA_SESSION_RX_CONSTRAINT_EVENT_ID)
		wlcore_event_ba_rx_constraint(wl,
				le16_to_cpu(mbox->rx_ba_role_id_bitmap),
				le16_to_cpu(mbox->rx_ba_allowed_bitmap));

	if (vector & BSS_LOSS_EVENT_ID)
		wlcore_event_beacon_loss(wl,
					 le16_to_cpu(mbox->bss_loss_bitmap));

	if (vector & CHANNEL_SWITCH_COMPLETE_EVENT_ID)
		wlcore_event_channel_switch(wl,
			le16_to_cpu(mbox->channel_switch_role_id_bitmap),
			true);

	if (vector & DUMMY_PACKET_EVENT_ID)
		wlcore_event_dummy_packet(wl);

	/*
	 * "TX retries exceeded" has a different meaning according to mode.
	 * In AP mode the offending station is disconnected.
	 */
	if (vector & MAX_TX_FAILURE_EVENT_ID)
		wlcore_event_max_tx_failure(wl,
				le16_to_cpu(mbox->tx_retry_exceeded_bitmap));

	if (vector & INACTIVE_STA_EVENT_ID)
		wlcore_event_inactive_sta(wl,
				le16_to_cpu(mbox->inactive_sta_bitmap));

	if (vector & REMAIN_ON_CHANNEL_COMPLETE_EVENT_ID)
		wlcore_event_roc_complete(wl);

	if (vector & SMART_CONFIG_SYNC_EVENT_ID)
		wlcore_smart_config_sync_event(wl, mbox->sc_sync_channel,
					       mbox->sc_sync_band);

	if (vector & SMART_CONFIG_DECODE_EVENT_ID)
		wlcore_smart_config_decode_event(wl,
						 mbox->sc_ssid_len,
						 mbox->sc_ssid,
						 mbox->sc_pwd_len,
						 mbox->sc_pwd);
	if (vector & FW_LOGGER_INDICATION)
		wlcore_event_fw_logger(wl);

	if (vector & RX_BA_WIN_SIZE_CHANGE_EVENT_ID) {
		struct wl12xx_vif *wlvif;
		struct ieee80211_vif *vif;
		struct ieee80211_sta *sta;
		u8 link_id = mbox->rx_ba_link_id;
		u8 win_size = mbox->rx_ba_win_size;
		const u8 *addr;

		wlvif = wl->links[link_id].wlvif;
		vif = wl12xx_wlvif_to_vif(wlvif);

		/* Update RX aggregation window size and call
		 * MAC routine to stop active RX aggregations for this link
		 */
		if (wlvif->bss_type != BSS_TYPE_AP_BSS)
			addr = vif->bss_conf.bssid;
		else
			addr = wl->links[link_id].addr;

		sta = ieee80211_find_sta(vif, addr);
		if (sta) {
			sta->max_rx_aggregation_subframes = win_size;
			ieee80211_stop_rx_ba_session(vif,
						wl->links[link_id].ba_bitmap,
						addr);
		}
	}

	return 0;
}