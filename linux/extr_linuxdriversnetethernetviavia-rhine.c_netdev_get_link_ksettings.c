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
struct rhine_private {int /*<<< orphan*/  task_lock; int /*<<< orphan*/  mii_if; } ;
struct net_device {int dummy; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mii_ethtool_get_link_ksettings (int /*<<< orphan*/ *,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rhine_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int netdev_get_link_ksettings(struct net_device *dev,
				     struct ethtool_link_ksettings *cmd)
{
	struct rhine_private *rp = netdev_priv(dev);

	mutex_lock(&rp->task_lock);
	mii_ethtool_get_link_ksettings(&rp->mii_if, cmd);
	mutex_unlock(&rp->task_lock);

	return 0;
}