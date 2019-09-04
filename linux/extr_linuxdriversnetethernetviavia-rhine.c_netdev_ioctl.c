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
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int generic_mii_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rhine_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  rhine_set_carrier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netdev_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct rhine_private *rp = netdev_priv(dev);
	int rc;

	if (!netif_running(dev))
		return -EINVAL;

	mutex_lock(&rp->task_lock);
	rc = generic_mii_ioctl(&rp->mii_if, if_mii(rq), cmd, NULL);
	rhine_set_carrier(&rp->mii_if);
	mutex_unlock(&rp->task_lock);

	return rc;
}