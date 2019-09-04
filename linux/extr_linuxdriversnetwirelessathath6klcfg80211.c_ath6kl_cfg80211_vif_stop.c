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
typedef  int u8 ;
struct cfg80211_scan_info {int aborted; } ;
struct ath6kl_vif {int nw_type; int* bssid; int /*<<< orphan*/ * scan_req; int /*<<< orphan*/  disconnect_timer; int /*<<< orphan*/  flags; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int AP_NETWORK ; 
 int /*<<< orphan*/  CONNECTED ; 
 int /*<<< orphan*/  CONNECT_PEND ; 
 int /*<<< orphan*/  DISCONNECT_CMD ; 
 int /*<<< orphan*/  WLAN_ENABLED ; 
 int /*<<< orphan*/  ath6kl_cfg80211_sta_bmiss_enhance (struct ath6kl_vif*,int) ; 
 int /*<<< orphan*/  ath6kl_disconnect (struct ath6kl_vif*) ; 
 int /*<<< orphan*/  ath6kl_disconnect_event (struct ath6kl_vif*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_scan_done (int /*<<< orphan*/ *,struct cfg80211_scan_info*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath6kl_cfg80211_vif_stop(struct ath6kl_vif *vif, bool wmi_ready)
{
	static u8 bcast_mac[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	bool discon_issued;

	netif_stop_queue(vif->ndev);

	clear_bit(WLAN_ENABLED, &vif->flags);

	if (wmi_ready) {
		discon_issued = test_bit(CONNECTED, &vif->flags) ||
				test_bit(CONNECT_PEND, &vif->flags);
		ath6kl_disconnect(vif);
		del_timer(&vif->disconnect_timer);

		if (discon_issued)
			ath6kl_disconnect_event(vif, DISCONNECT_CMD,
						(vif->nw_type & AP_NETWORK) ?
						bcast_mac : vif->bssid,
						0, NULL, 0);
	}

	if (vif->scan_req) {
		struct cfg80211_scan_info info = {
			.aborted = true,
		};

		cfg80211_scan_done(vif->scan_req, &info);
		vif->scan_req = NULL;
	}

	/* need to clean up enhanced bmiss detection fw state */
	ath6kl_cfg80211_sta_bmiss_enhance(vif, false);
}