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
struct net_device {int dummy; } ;
struct net_bridge {int dummy; } ;
struct ifreq {int /*<<< orphan*/  ifr_ifindex; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SIOCBRADDIF 130 
#define  SIOCBRDELIF 129 
#define  SIOCDEVPRIVATE 128 
 int add_del_if (struct net_bridge*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  br_debug (struct net_bridge*,char*,int) ; 
 struct net_bridge* netdev_priv (struct net_device*) ; 
 int old_dev_ioctl (struct net_device*,struct ifreq*,int) ; 

int br_dev_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct net_bridge *br = netdev_priv(dev);

	switch (cmd) {
	case SIOCDEVPRIVATE:
		return old_dev_ioctl(dev, rq, cmd);

	case SIOCBRADDIF:
	case SIOCBRDELIF:
		return add_del_if(br, rq->ifr_ifindex, cmd == SIOCBRADDIF);

	}

	br_debug(br, "Bridge does not support ioctl 0x%x\n", cmd);
	return -EOPNOTSUPP;
}