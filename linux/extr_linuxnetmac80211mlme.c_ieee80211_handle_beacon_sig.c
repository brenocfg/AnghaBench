#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int driver_flags; } ;
struct ieee80211_sub_if_data {TYPE_3__ vif; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  signal; } ;
struct ieee80211_local {int dummy; } ;
struct ieee80211_if_managed {int flags; int last_cqm_event_signal; int count_beacon_signal; int last_ave_beacon_signal; scalar_t__ rssi_min_thold; scalar_t__ rssi_max_thold; int /*<<< orphan*/  ave_beacon_signal; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__ rssi; } ;
struct ieee80211_event {TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct ieee80211_bss_conf {int cqm_rssi_thold; int cqm_rssi_hyst; int cqm_rssi_low; int cqm_rssi_high; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_SIGNAL_AVE_MIN_COUNT ; 
 int IEEE80211_STA_RESET_SIGNAL_AVE ; 
 int IEEE80211_VIF_SUPPORTS_CQM_RSSI ; 
 int /*<<< orphan*/  NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH ; 
 int /*<<< orphan*/  NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW ; 
 int /*<<< orphan*/  RSSI_EVENT ; 
 int /*<<< orphan*/  RSSI_EVENT_HIGH ; 
 int /*<<< orphan*/  RSSI_EVENT_LOW ; 
 int /*<<< orphan*/  drv_event_callback (struct ieee80211_local*,struct ieee80211_sub_if_data*,struct ieee80211_event*) ; 
 int /*<<< orphan*/  ewma_beacon_signal_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ewma_beacon_signal_init (int /*<<< orphan*/ *) ; 
 int ewma_beacon_signal_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_cqm_rssi_notify (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_handle_beacon_sig(struct ieee80211_sub_if_data *sdata,
					struct ieee80211_if_managed *ifmgd,
					struct ieee80211_bss_conf *bss_conf,
					struct ieee80211_local *local,
					struct ieee80211_rx_status *rx_status)
{
	/* Track average RSSI from the Beacon frames of the current AP */

	if (ifmgd->flags & IEEE80211_STA_RESET_SIGNAL_AVE) {
		ifmgd->flags &= ~IEEE80211_STA_RESET_SIGNAL_AVE;
		ewma_beacon_signal_init(&ifmgd->ave_beacon_signal);
		ifmgd->last_cqm_event_signal = 0;
		ifmgd->count_beacon_signal = 1;
		ifmgd->last_ave_beacon_signal = 0;
	} else {
		ifmgd->count_beacon_signal++;
	}

	ewma_beacon_signal_add(&ifmgd->ave_beacon_signal, -rx_status->signal);

	if (ifmgd->rssi_min_thold != ifmgd->rssi_max_thold &&
	    ifmgd->count_beacon_signal >= IEEE80211_SIGNAL_AVE_MIN_COUNT) {
		int sig = -ewma_beacon_signal_read(&ifmgd->ave_beacon_signal);
		int last_sig = ifmgd->last_ave_beacon_signal;
		struct ieee80211_event event = {
			.type = RSSI_EVENT,
		};

		/*
		 * if signal crosses either of the boundaries, invoke callback
		 * with appropriate parameters
		 */
		if (sig > ifmgd->rssi_max_thold &&
		    (last_sig <= ifmgd->rssi_min_thold || last_sig == 0)) {
			ifmgd->last_ave_beacon_signal = sig;
			event.u.rssi.data = RSSI_EVENT_HIGH;
			drv_event_callback(local, sdata, &event);
		} else if (sig < ifmgd->rssi_min_thold &&
			   (last_sig >= ifmgd->rssi_max_thold ||
			   last_sig == 0)) {
			ifmgd->last_ave_beacon_signal = sig;
			event.u.rssi.data = RSSI_EVENT_LOW;
			drv_event_callback(local, sdata, &event);
		}
	}

	if (bss_conf->cqm_rssi_thold &&
	    ifmgd->count_beacon_signal >= IEEE80211_SIGNAL_AVE_MIN_COUNT &&
	    !(sdata->vif.driver_flags & IEEE80211_VIF_SUPPORTS_CQM_RSSI)) {
		int sig = -ewma_beacon_signal_read(&ifmgd->ave_beacon_signal);
		int last_event = ifmgd->last_cqm_event_signal;
		int thold = bss_conf->cqm_rssi_thold;
		int hyst = bss_conf->cqm_rssi_hyst;

		if (sig < thold &&
		    (last_event == 0 || sig < last_event - hyst)) {
			ifmgd->last_cqm_event_signal = sig;
			ieee80211_cqm_rssi_notify(
				&sdata->vif,
				NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW,
				sig, GFP_KERNEL);
		} else if (sig > thold &&
			   (last_event == 0 || sig > last_event + hyst)) {
			ifmgd->last_cqm_event_signal = sig;
			ieee80211_cqm_rssi_notify(
				&sdata->vif,
				NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH,
				sig, GFP_KERNEL);
		}
	}

	if (bss_conf->cqm_rssi_low &&
	    ifmgd->count_beacon_signal >= IEEE80211_SIGNAL_AVE_MIN_COUNT) {
		int sig = -ewma_beacon_signal_read(&ifmgd->ave_beacon_signal);
		int last_event = ifmgd->last_cqm_event_signal;
		int low = bss_conf->cqm_rssi_low;
		int high = bss_conf->cqm_rssi_high;

		if (sig < low &&
		    (last_event == 0 || last_event >= low)) {
			ifmgd->last_cqm_event_signal = sig;
			ieee80211_cqm_rssi_notify(
				&sdata->vif,
				NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW,
				sig, GFP_KERNEL);
		} else if (sig > high &&
			   (last_event == 0 || last_event <= high)) {
			ifmgd->last_cqm_event_signal = sig;
			ieee80211_cqm_rssi_notify(
				&sdata->vif,
				NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH,
				sig, GFP_KERNEL);
		}
	}
}