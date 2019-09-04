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
typedef  int /*<<< orphan*/  uint32_t ;
struct wol_config {int dummy; } ;
struct lbs_private {int is_host_sleep_activated; scalar_t__ psstate; int /*<<< orphan*/  dev; int /*<<< orphan*/  host_sleep_q; int /*<<< orphan*/  wol_criteria; } ;
struct cmd_header {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_HOST_SLEEP_ACTIVATE ; 
 int /*<<< orphan*/  EHS_REMOVE_WAKEUP ; 
 int HZ ; 
 scalar_t__ PS_STATE_FULL_POWER ; 
 int __lbs_cmd (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_header*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lbs_host_sleep_cfg (struct lbs_private*,int /*<<< orphan*/ ,struct wol_config*) ; 
 int /*<<< orphan*/  lbs_ret_host_sleep_activate ; 
 int /*<<< orphan*/  memset (struct cmd_header*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

int lbs_set_host_sleep(struct lbs_private *priv, int host_sleep)
{
	struct cmd_header cmd;
	int ret = 0;
	uint32_t criteria = EHS_REMOVE_WAKEUP;

	if (host_sleep) {
		if (priv->is_host_sleep_activated != 1) {
			memset(&cmd, 0, sizeof(cmd));
			ret = lbs_host_sleep_cfg(priv, priv->wol_criteria,
					(struct wol_config *)NULL);
			if (ret) {
				netdev_info(priv->dev,
					    "Host sleep configuration failed: %d\n",
					    ret);
				return ret;
			}
			if (priv->psstate == PS_STATE_FULL_POWER) {
				ret = __lbs_cmd(priv,
						CMD_802_11_HOST_SLEEP_ACTIVATE,
						&cmd,
						sizeof(cmd),
						lbs_ret_host_sleep_activate, 0);
				if (ret)
					netdev_info(priv->dev,
						    "HOST_SLEEP_ACTIVATE failed: %d\n",
						    ret);
			}

			if (!wait_event_interruptible_timeout(
						priv->host_sleep_q,
						priv->is_host_sleep_activated,
						(10 * HZ))) {
				netdev_err(priv->dev,
					   "host_sleep_q: timer expired\n");
				ret = -1;
			}
		} else {
			netdev_err(priv->dev, "host sleep: already enabled\n");
		}
	} else {
		if (priv->is_host_sleep_activated)
			ret = lbs_host_sleep_cfg(priv, criteria,
					(struct wol_config *)NULL);
	}

	return ret;
}