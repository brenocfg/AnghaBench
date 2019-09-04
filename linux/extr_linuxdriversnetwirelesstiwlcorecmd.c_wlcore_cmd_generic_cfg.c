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
typedef  void* u8 ;
struct wlcore_cmd_generic_cfg {void* value; void* enable; void* feature; int /*<<< orphan*/  role_id; } ;
struct wl12xx_vif {int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GENERIC_CFG ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wlcore_cmd_generic_cfg*) ; 
 struct wlcore_cmd_generic_cfg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wlcore_cmd_generic_cfg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,void*,void*) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int wlcore_cmd_generic_cfg(struct wl1271 *wl, struct wl12xx_vif *wlvif,
			   u8 feature, u8 enable, u8 value)
{
	struct wlcore_cmd_generic_cfg *cmd;
	int ret;

	wl1271_debug(DEBUG_CMD,
		     "cmd generic cfg (role %d feature %d enable %d value %d)",
		     wlvif->role_id, feature, enable, value);

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	cmd->role_id = wlvif->role_id;
	cmd->feature = feature;
	cmd->enable = enable;
	cmd->value = value;

	ret = wl1271_cmd_send(wl, CMD_GENERIC_CFG, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to send generic cfg command");
		goto out_free;
	}
out_free:
	kfree(cmd);
	return ret;
}