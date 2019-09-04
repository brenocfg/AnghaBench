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
struct wl18xx_cmd_dfs_radar_debug {int /*<<< orphan*/  channel; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DFS_RADAR_DETECTION_DEBUG ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl18xx_cmd_dfs_radar_debug*) ; 
 struct wl18xx_cmd_dfs_radar_debug* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl18xx_cmd_dfs_radar_debug*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int wl18xx_cmd_radar_detection_debug(struct wl1271 *wl, u8 channel)
{
	struct wl18xx_cmd_dfs_radar_debug *cmd;
	int ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd radar detection debug (chan %d)",
		     channel);

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd)
		return -ENOMEM;

	cmd->channel = channel;

	ret = wl1271_cmd_send(wl, CMD_DFS_RADAR_DETECTION_DEBUG,
			      cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to send radar detection debug command");
		goto out_free;
	}

out_free:
	kfree(cmd);
	return ret;
}