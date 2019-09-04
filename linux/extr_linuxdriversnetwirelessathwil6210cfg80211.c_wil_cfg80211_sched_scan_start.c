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
struct wiphy {int dummy; } ;
struct wil6210_vif {scalar_t__ mid; } ;
struct wil6210_priv {int dummy; } ;
struct net_device {int dummy; } ;
struct cfg80211_sched_scan_request {int n_ssids; int n_channels; int n_match_sets; int n_scan_plans; int /*<<< orphan*/  ie; int /*<<< orphan*/  ie_len; struct cfg80211_sched_scan_plan* scan_plans; struct cfg80211_match_set* match_sets; int /*<<< orphan*/  delay; int /*<<< orphan*/  min_rssi_thold; TYPE_2__** channels; TYPE_1__* ssids; int /*<<< orphan*/  flags; } ;
struct cfg80211_sched_scan_plan {int /*<<< orphan*/  iterations; int /*<<< orphan*/  interval; } ;
struct TYPE_6__ {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct cfg80211_match_set {TYPE_3__ ssid; int /*<<< orphan*/  rssi_thold; } ;
struct TYPE_5__ {int /*<<< orphan*/  hw_value; } ;
struct TYPE_4__ {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WMI_FRAME_PROBE_REQ ; 
 struct wil6210_vif* ndev_to_vif (struct net_device*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,...) ; 
 int /*<<< orphan*/  wil_hex_dump_misc (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct wil6210_priv* wiphy_to_wil (struct wiphy*) ; 
 int wmi_set_ie (struct wil6210_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wmi_start_sched_scan (struct wil6210_priv*,struct cfg80211_sched_scan_request*) ; 

__attribute__((used)) static int
wil_cfg80211_sched_scan_start(struct wiphy *wiphy,
			      struct net_device *dev,
			      struct cfg80211_sched_scan_request *request)
{
	struct wil6210_priv *wil = wiphy_to_wil(wiphy);
	struct wil6210_vif *vif = ndev_to_vif(dev);
	int i, rc;

	if (vif->mid != 0)
		return -EOPNOTSUPP;

	wil_dbg_misc(wil,
		     "sched scan start: n_ssids %d, ie_len %zu, flags 0x%x\n",
		     request->n_ssids, request->ie_len, request->flags);
	for (i = 0; i < request->n_ssids; i++) {
		wil_dbg_misc(wil, "SSID[%d]:", i);
		wil_hex_dump_misc("SSID ", DUMP_PREFIX_OFFSET, 16, 1,
				  request->ssids[i].ssid,
				  request->ssids[i].ssid_len, true);
	}
	wil_dbg_misc(wil, "channels:");
	for (i = 0; i < request->n_channels; i++)
		wil_dbg_misc(wil, " %d%s", request->channels[i]->hw_value,
			     i == request->n_channels - 1 ? "\n" : "");
	wil_dbg_misc(wil, "n_match_sets %d, min_rssi_thold %d, delay %d\n",
		     request->n_match_sets, request->min_rssi_thold,
		     request->delay);
	for (i = 0; i < request->n_match_sets; i++) {
		struct cfg80211_match_set *ms = &request->match_sets[i];

		wil_dbg_misc(wil, "MATCHSET[%d]: rssi_thold %d\n",
			     i, ms->rssi_thold);
		wil_hex_dump_misc("SSID ", DUMP_PREFIX_OFFSET, 16, 1,
				  ms->ssid.ssid,
				  ms->ssid.ssid_len, true);
	}
	wil_dbg_misc(wil, "n_scan_plans %d\n", request->n_scan_plans);
	for (i = 0; i < request->n_scan_plans; i++) {
		struct cfg80211_sched_scan_plan *sp = &request->scan_plans[i];

		wil_dbg_misc(wil, "SCAN PLAN[%d]: interval %d iterations %d\n",
			     i, sp->interval, sp->iterations);
	}

	rc = wmi_set_ie(vif, WMI_FRAME_PROBE_REQ,
			request->ie_len, request->ie);
	if (rc)
		return rc;
	return wmi_start_sched_scan(wil, request);
}