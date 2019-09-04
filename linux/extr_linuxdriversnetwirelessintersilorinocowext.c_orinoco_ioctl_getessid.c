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
struct orinoco_private {int /*<<< orphan*/  desired_essid; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_point {int length; int flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IW_ESSID_MAX_SIZE ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int orinoco_hw_get_essid (struct orinoco_private*,int*,char*) ; 
 scalar_t__ orinoco_lock (struct orinoco_private*,unsigned long*) ; 
 int /*<<< orphan*/  orinoco_unlock (struct orinoco_private*,unsigned long*) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int orinoco_ioctl_getessid(struct net_device *dev,
				  struct iw_request_info *info,
				  struct iw_point *erq,
				  char *essidbuf)
{
	struct orinoco_private *priv = ndev_priv(dev);
	int active;
	int err = 0;
	unsigned long flags;

	if (netif_running(dev)) {
		err = orinoco_hw_get_essid(priv, &active, essidbuf);
		if (err < 0)
			return err;
		erq->length = err;
	} else {
		if (orinoco_lock(priv, &flags) != 0)
			return -EBUSY;
		memcpy(essidbuf, priv->desired_essid, IW_ESSID_MAX_SIZE);
		erq->length = strlen(priv->desired_essid);
		orinoco_unlock(priv, &flags);
	}

	erq->flags = 1;

	return 0;
}