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
struct sockaddr {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
struct orinoco_private {int dummy; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int EBUSY ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 int orinoco_hw_get_current_bssid (struct orinoco_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 

__attribute__((used)) static int orinoco_ioctl_getwap(struct net_device *dev,
				struct iw_request_info *info,
				struct sockaddr *ap_addr,
				char *extra)
{
	struct orinoco_private *priv = ndev_priv(dev);

	int err = 0;
	unsigned long flags;

	if (orinoco_lock(priv, &flags) != 0)
		return -EBUSY;

	ap_addr->sa_family = ARPHRD_ETHER;
	err = orinoco_hw_get_current_bssid(priv, ap_addr->sa_data);

	orinoco_unlock(priv, &flags);

	return err;
}