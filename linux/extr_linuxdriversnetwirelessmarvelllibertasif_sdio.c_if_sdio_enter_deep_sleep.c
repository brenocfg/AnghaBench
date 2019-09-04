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
struct lbs_private {int /*<<< orphan*/  dev; } ;
struct cmd_header {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_DEEP_SLEEP ; 
 int __lbs_cmd (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_header*,int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  lbs_cmd_copyback ; 
 int /*<<< orphan*/  lbs_deb_sdio (char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memset (struct cmd_header*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int if_sdio_enter_deep_sleep(struct lbs_private *priv)
{
	int ret = -1;
	struct cmd_header cmd;

	memset(&cmd, 0, sizeof(cmd));

	lbs_deb_sdio("send DEEP_SLEEP command\n");
	ret = __lbs_cmd(priv, CMD_802_11_DEEP_SLEEP, &cmd, sizeof(cmd),
			lbs_cmd_copyback, (unsigned long) &cmd);
	if (ret)
		netdev_err(priv->dev, "DEEP_SLEEP cmd failed\n");

	mdelay(200);
	return ret;
}