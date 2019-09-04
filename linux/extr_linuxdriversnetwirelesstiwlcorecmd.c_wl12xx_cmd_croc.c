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
struct wl12xx_cmd_croc {int /*<<< orphan*/  role_id; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CANCEL_REMAIN_ON_CHANNEL ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct wl12xx_cmd_croc*) ; 
 struct wl12xx_cmd_croc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_cmd_croc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

__attribute__((used)) static int wl12xx_cmd_croc(struct wl1271 *wl, u8 role_id)
{
	struct wl12xx_cmd_croc *cmd;
	int ret = 0;

	wl1271_debug(DEBUG_CMD, "cmd croc (%d)", role_id);

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}
	cmd->role_id = role_id;

	ret = wl1271_cmd_send(wl, CMD_CANCEL_REMAIN_ON_CHANNEL, cmd,
			      sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to send ROC command");
		goto out_free;
	}

out_free:
	kfree(cmd);

out:
	return ret;
}