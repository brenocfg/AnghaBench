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
struct wpan_dev {int /*<<< orphan*/  iftype; } ;
struct net_device {int dummy; } ;
struct ieee802154_sub_if_data {struct wpan_dev wpan_dev; } ;

/* Variables and functions */
 struct ieee802154_sub_if_data* IEEE802154_DEV_TO_SUB_IF (struct net_device*) ; 
 int ieee802154_check_concurrent_iface (struct ieee802154_sub_if_data*,int /*<<< orphan*/ ) ; 
 int mac802154_slave_open (struct net_device*) ; 

__attribute__((used)) static int mac802154_wpan_open(struct net_device *dev)
{
	int rc;
	struct ieee802154_sub_if_data *sdata = IEEE802154_DEV_TO_SUB_IF(dev);
	struct wpan_dev *wpan_dev = &sdata->wpan_dev;

	rc = ieee802154_check_concurrent_iface(sdata, wpan_dev->iftype);
	if (rc < 0)
		return rc;

	return mac802154_slave_open(dev);
}