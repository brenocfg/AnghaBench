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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mwifiex_private {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  HostCmd_CMD_FUNC_INIT ; 
 int /*<<< orphan*/  HostCmd_CMD_FUNC_SHUTDOWN ; 
 scalar_t__ MWIFIEX_FUNC_INIT ; 
 scalar_t__ MWIFIEX_FUNC_SHUTDOWN ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int mwifiex_init_shutdown_fw(struct mwifiex_private *priv,
			     u32 func_init_shutdown)
{
	u16 cmd;

	if (func_init_shutdown == MWIFIEX_FUNC_INIT) {
		cmd = HostCmd_CMD_FUNC_INIT;
	} else if (func_init_shutdown == MWIFIEX_FUNC_SHUTDOWN) {
		cmd = HostCmd_CMD_FUNC_SHUTDOWN;
	} else {
		mwifiex_dbg(priv->adapter, ERROR,
			    "unsupported parameter\n");
		return -1;
	}

	return mwifiex_send_cmd(priv, cmd, HostCmd_ACT_GEN_SET, 0, NULL, true);
}