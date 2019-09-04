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
typedef  int /*<<< orphan*/  u8 ;
struct wl12xx_vif {scalar_t__ bss_type; int /*<<< orphan*/  wmm_enabled; } ;
struct wl12xx_cmd_set_peer_state {int /*<<< orphan*/  wmm; int /*<<< orphan*/  state; int /*<<< orphan*/  hlid; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 scalar_t__ BSS_TYPE_STA_BSS ; 
 int /*<<< orphan*/  CMD_SET_PEER_STATE ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WL1271_CMD_STA_STATE_CONNECTED ; 
 int /*<<< orphan*/  kfree (struct wl12xx_cmd_set_peer_state*) ; 
 struct wl12xx_cmd_set_peer_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_cmd_set_peer_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int wl12xx_cmd_set_peer_state(struct wl1271 *wl, struct wl12xx_vif *wlvif,
			      u8 hlid)
{
	struct wl12xx_cmd_set_peer_state *cmd;
	int ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd set peer state (hlid=%d)", hlid);

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	cmd->hlid = hlid;
	cmd->state = WL1271_CMD_STA_STATE_CONNECTED;

	/* wmm param is valid only for station role */
	if (wlvif->bss_type == BSS_TYPE_STA_BSS)
		cmd->wmm = wlvif->wmm_enabled;

	ret = wl1271_cmd_send(wl, CMD_SET_PEER_STATE, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to send set peer state command");
		goto out_free;
	}

out_free:
	kfree(cmd);

out:
	return ret;
}