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
struct qeth_card {TYPE_1__* gdev; } ;
struct net_device {int /*<<< orphan*/  features; struct qeth_card* ml_priv; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_HW_FEATURES ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  netdev_update_features (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

void qeth_enable_hw_features(struct net_device *dev)
{
	struct qeth_card *card = dev->ml_priv;
	netdev_features_t features;

	rtnl_lock();
	features = dev->features;
	/* force-off any feature that needs an IPA sequence.
	 * netdev_update_features() will restart them.
	 */
	dev->features &= ~QETH_HW_FEATURES;
	netdev_update_features(dev);
	if (features != dev->features)
		dev_warn(&card->gdev->dev,
			 "Device recovery failed to restore all offload features\n");
	rtnl_unlock();
}