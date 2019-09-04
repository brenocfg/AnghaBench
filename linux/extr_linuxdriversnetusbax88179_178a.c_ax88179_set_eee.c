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
struct usbnet {int /*<<< orphan*/  mii; scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct ethtool_eee {int /*<<< orphan*/  eee_enabled; } ;
struct ax88179_data {int /*<<< orphan*/  eee_enabled; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ax88179_chk_eee (struct usbnet*) ; 
 int /*<<< orphan*/  ax88179_disable_eee (struct usbnet*) ; 
 int /*<<< orphan*/  ax88179_enable_eee (struct usbnet*) ; 
 int ax88179_ethtool_set_eee (struct usbnet*,struct ethtool_eee*) ; 
 int /*<<< orphan*/  mii_nway_restart (int /*<<< orphan*/ *) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  usbnet_link_change (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ax88179_set_eee(struct net_device *net, struct ethtool_eee *edata)
{
	struct usbnet *dev = netdev_priv(net);
	struct ax88179_data *priv = (struct ax88179_data *)dev->data;
	int ret = -EOPNOTSUPP;

	priv->eee_enabled = edata->eee_enabled;
	if (!priv->eee_enabled) {
		ax88179_disable_eee(dev);
	} else {
		priv->eee_enabled = ax88179_chk_eee(dev);
		if (!priv->eee_enabled)
			return -EOPNOTSUPP;

		ax88179_enable_eee(dev);
	}

	ret = ax88179_ethtool_set_eee(dev, edata);
	if (ret)
		return ret;

	mii_nway_restart(&dev->mii);

	usbnet_link_change(dev, 0, 0);

	return ret;
}