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
struct wiphy {int dummy; } ;
struct net_device {int dummy; } ;
struct lbs_private {struct net_device* mesh_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct cmd_ds_802_11_ad_hoc_stop {TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_AD_HOC_STOP ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_ad_hoc_stop*) ; 
 int /*<<< orphan*/  lbs_mac_event_disconnected (struct lbs_private*,int) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_802_11_ad_hoc_stop*,int /*<<< orphan*/ ,int) ; 
 struct lbs_private* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int lbs_leave_ibss(struct wiphy *wiphy, struct net_device *dev)
{
	struct lbs_private *priv = wiphy_priv(wiphy);
	struct cmd_ds_802_11_ad_hoc_stop cmd;
	int ret = 0;

	if (dev == priv->mesh_dev)
		return -EOPNOTSUPP;

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	ret = lbs_cmd_with_response(priv, CMD_802_11_AD_HOC_STOP, &cmd);

	/* TODO: consider doing this at MACREG_INT_CODE_ADHOC_BCN_LOST time */
	lbs_mac_event_disconnected(priv, true);

	return ret;
}