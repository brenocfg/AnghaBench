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
typedef  scalar_t__ u8 ;
struct wl12xx_cmd_role_enable {scalar_t__ role_id; scalar_t__ role_type; int /*<<< orphan*/  mac_address; } ;
struct wl1271 {int /*<<< orphan*/  roles_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_ROLE_ENABLE ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WL12XX_INVALID_ROLE_ID ; 
 scalar_t__ WL12XX_MAX_ROLES ; 
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct wl12xx_cmd_role_enable*) ; 
 struct wl12xx_cmd_role_enable* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_send (struct wl1271*,int /*<<< orphan*/ ,struct wl12xx_cmd_role_enable*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 

int wl12xx_cmd_role_enable(struct wl1271 *wl, u8 *addr, u8 role_type,
			   u8 *role_id)
{
	struct wl12xx_cmd_role_enable *cmd;
	int ret;

	wl1271_debug(DEBUG_CMD, "cmd role enable");

	if (WARN_ON(*role_id != WL12XX_INVALID_ROLE_ID))
		return -EBUSY;

	cmd = kzalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd) {
		ret = -ENOMEM;
		goto out;
	}

	/* get role id */
	cmd->role_id = find_first_zero_bit(wl->roles_map, WL12XX_MAX_ROLES);
	if (cmd->role_id >= WL12XX_MAX_ROLES) {
		ret = -EBUSY;
		goto out_free;
	}

	memcpy(cmd->mac_address, addr, ETH_ALEN);
	cmd->role_type = role_type;

	ret = wl1271_cmd_send(wl, CMD_ROLE_ENABLE, cmd, sizeof(*cmd), 0);
	if (ret < 0) {
		wl1271_error("failed to initiate cmd role enable");
		goto out_free;
	}

	__set_bit(cmd->role_id, wl->roles_map);
	*role_id = cmd->role_id;

out_free:
	kfree(cmd);

out:
	return ret;
}