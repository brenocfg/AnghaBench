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
struct wl12xx_vif {size_t dev_hlid; int /*<<< orphan*/  dev_role_id; } ;
struct TYPE_2__ {size_t hlid; int /*<<< orphan*/  session; } ;
struct wl12xx_cmd_role_start {int channel; TYPE_1__ device; int /*<<< orphan*/  role_id; int /*<<< orphan*/  band; } ;
struct wl1271 {int /*<<< orphan*/ * session_ids; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ROLE_START ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NL80211_BAND_5GHZ ; 
 size_t WL12XX_INVALID_LINK_ID ; 
 int /*<<< orphan*/  WLCORE_BAND_5GHZ ; 
 int /*<<< orphan*/  kfree (struct wl12xx_cmd_role_start*) ; 
 struct wl12xx_cmd_role_start* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_cmd_role_start*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 int wl12xx_allocate_link (struct wl1271*,struct wl12xx_vif*,size_t*) ; 
 int /*<<< orphan*/  wl12xx_free_link (struct wl1271*,struct wl12xx_vif*,size_t*) ; 

__attribute__((used)) static int wl12xx_cmd_role_start_dev(struct wl1271 *wl,
				     struct wl12xx_vif *wlvif,
				     enum nl80211_band band,
				     int channel)
{
	struct wl12xx_cmd_role_start *cmd;
	int ret;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	wl1271_debug(DEBUG_CMD, "cmd role start dev %d", wlvif->dev_role_id);

	cmd->role_id = wlvif->dev_role_id;
	if (band == NL80211_BAND_5GHZ)
		cmd->band = WLCORE_BAND_5GHZ;
	cmd->channel = channel;

	if (wlvif->dev_hlid == WL12XX_INVALID_LINK_ID) {
		ret = wl12xx_allocate_link(wl, wlvif, &wlvif->dev_hlid);
		if (ret)
			goto out_free;
	}
	cmd->device.hlid = wlvif->dev_hlid;
	cmd->device.session = wl->session_ids[wlvif->dev_hlid];

	wl1271_debug(DEBUG_CMD, "role start: roleid=%d, hlid=%d, session=%d",
		     cmd->role_id, cmd->device.hlid, cmd->device.session);

	ret = wl1271_cmd_send(wl, CMD_ROLE_START, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to initiate cmd role enable");
		goto err_hlid;
	}

	goto out_free;

err_hlid:
	/* clear links on error */
	wl12xx_free_link(wl, wlvif, &wlvif->dev_hlid);

out_free:
	kfree(cmd);

out:
	return ret;
}