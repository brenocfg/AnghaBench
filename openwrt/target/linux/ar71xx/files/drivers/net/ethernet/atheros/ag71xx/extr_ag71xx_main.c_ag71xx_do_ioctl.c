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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct ag71xx {int /*<<< orphan*/ * phy_dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int EOPNOTSUPP ; 
#define  SIOCGIFHWADDR 132 
#define  SIOCGMIIPHY 131 
#define  SIOCGMIIREG 130 
#define  SIOCSIFHWADDR 129 
#define  SIOCSMIIREG 128 
 int /*<<< orphan*/  copy_from_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  copy_to_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ag71xx* netdev_priv (struct net_device*) ; 
 int phy_mii_ioctl (int /*<<< orphan*/ *,struct ifreq*,int) ; 

__attribute__((used)) static int ag71xx_do_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct ag71xx *ag = netdev_priv(dev);

	switch (cmd) {
	case SIOCSIFHWADDR:
		if (copy_from_user
			(dev->dev_addr, ifr->ifr_data, sizeof(dev->dev_addr)))
			return -EFAULT;
		return 0;

	case SIOCGIFHWADDR:
		if (copy_to_user
			(ifr->ifr_data, dev->dev_addr, sizeof(dev->dev_addr)))
			return -EFAULT;
		return 0;

	case SIOCGMIIPHY:
	case SIOCGMIIREG:
	case SIOCSMIIREG:
		if (ag->phy_dev == NULL)
			break;

		return phy_mii_ioctl(ag->phy_dev, ifr, cmd);

	default:
		break;
	}

	return -EOPNOTSUPP;
}