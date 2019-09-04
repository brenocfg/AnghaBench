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
union iwreq_data {int /*<<< orphan*/  name; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ phy_type; } ;
struct ks_wlan_private {scalar_t__ sleep_mode; scalar_t__ dev_state; TYPE_1__ reg; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEVICE_STATE_READY ; 
 scalar_t__ D_11B_ONLY_MODE ; 
 scalar_t__ D_11G_ONLY_MODE ; 
 int EPERM ; 
 scalar_t__ SLP_SLEEP ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ks_wlan_get_name(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *cwrq,
			    char *extra)
{
	struct ks_wlan_private *priv = netdev_priv(dev);

	if (priv->sleep_mode == SLP_SLEEP)
		return -EPERM;

	/* for SLEEP MODE */
	if (priv->dev_state < DEVICE_STATE_READY)
		strcpy(cwrq->name, "NOT READY!");
	else if (priv->reg.phy_type == D_11B_ONLY_MODE)
		strcpy(cwrq->name, "IEEE 802.11b");
	else if (priv->reg.phy_type == D_11G_ONLY_MODE)
		strcpy(cwrq->name, "IEEE 802.11g");
	else
		strcpy(cwrq->name, "IEEE 802.11b/g");

	return 0;
}