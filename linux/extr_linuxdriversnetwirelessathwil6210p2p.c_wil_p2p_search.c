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
struct wil_p2p_info {int discovery_started; int /*<<< orphan*/  discovery_timer; int /*<<< orphan*/  discovery_expired_work; } ;
struct wil6210_vif {struct wil_p2p_info p2p; } ;
struct wil6210_priv {int /*<<< orphan*/  mutex; } ;
struct cfg80211_scan_request {int /*<<< orphan*/  ie; int /*<<< orphan*/  ie_len; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P2P_DEFAULT_BI ; 
 int /*<<< orphan*/  P2P_DMG_SOCIAL_CHANNEL ; 
 int /*<<< orphan*/  P2P_SEARCH_DURATION_MS ; 
 int /*<<< orphan*/  P2P_WILDCARD_SSID ; 
 int /*<<< orphan*/  WMI_FRAME_PROBE_REQ ; 
 int /*<<< orphan*/  WMI_FRAME_PROBE_RESP ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 struct wil6210_priv* vif_to_wil (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_p2p_search_expired ; 
 int wmi_p2p_cfg (struct wil6210_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wmi_set_ie (struct wil6210_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wmi_set_ssid (struct wil6210_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wmi_start_search (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wmi_stop_discovery (struct wil6210_vif*) ; 

int wil_p2p_search(struct wil6210_vif *vif,
		   struct cfg80211_scan_request *request)
{
	struct wil6210_priv *wil = vif_to_wil(vif);
	int rc;
	struct wil_p2p_info *p2p = &vif->p2p;

	wil_dbg_misc(wil, "p2p_search: channel %d\n", P2P_DMG_SOCIAL_CHANNEL);

	lockdep_assert_held(&wil->mutex);

	if (p2p->discovery_started) {
		wil_err(wil, "search failed. discovery already ongoing\n");
		rc = -EBUSY;
		goto out;
	}

	rc = wmi_p2p_cfg(vif, P2P_DMG_SOCIAL_CHANNEL, P2P_DEFAULT_BI);
	if (rc) {
		wil_err(wil, "wmi_p2p_cfg failed\n");
		goto out;
	}

	rc = wmi_set_ssid(vif, strlen(P2P_WILDCARD_SSID), P2P_WILDCARD_SSID);
	if (rc) {
		wil_err(wil, "wmi_set_ssid failed\n");
		goto out_stop;
	}

	/* Set application IE to probe request and probe response */
	rc = wmi_set_ie(vif, WMI_FRAME_PROBE_REQ,
			request->ie_len, request->ie);
	if (rc) {
		wil_err(wil, "wmi_set_ie(WMI_FRAME_PROBE_REQ) failed\n");
		goto out_stop;
	}

	/* supplicant doesn't provide Probe Response IEs. As a workaround -
	 * re-use Probe Request IEs
	 */
	rc = wmi_set_ie(vif, WMI_FRAME_PROBE_RESP,
			request->ie_len, request->ie);
	if (rc) {
		wil_err(wil, "wmi_set_ie(WMI_FRAME_PROBE_RESP) failed\n");
		goto out_stop;
	}

	rc = wmi_start_search(vif);
	if (rc) {
		wil_err(wil, "wmi_start_search failed\n");
		goto out_stop;
	}

	p2p->discovery_started = 1;
	INIT_WORK(&p2p->discovery_expired_work, wil_p2p_search_expired);
	mod_timer(&p2p->discovery_timer,
		  jiffies + msecs_to_jiffies(P2P_SEARCH_DURATION_MS));

out_stop:
	if (rc)
		wmi_stop_discovery(vif);

out:
	return rc;
}