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
struct velocity_info {int dummy; } ;
struct net_device {int dummy; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  PCI_D3hot ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 struct velocity_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int velocity_mii_ioctl (struct net_device*,struct ifreq*,int) ; 
 int /*<<< orphan*/  velocity_set_power_state (struct velocity_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int velocity_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct velocity_info *vptr = netdev_priv(dev);
	int ret;

	/* If we are asked for information and the device is power
	   saving then we need to bring the device back up to talk to it */

	if (!netif_running(dev))
		velocity_set_power_state(vptr, PCI_D0);

	switch (cmd) {
	case SIOCGMIIPHY:	/* Get address of MII PHY in use. */
	case SIOCGMIIREG:	/* Read MII PHY register. */
	case SIOCSMIIREG:	/* Write to MII PHY register. */
		ret = velocity_mii_ioctl(dev, rq, cmd);
		break;

	default:
		ret = -EOPNOTSUPP;
	}
	if (!netif_running(dev))
		velocity_set_power_state(vptr, PCI_D3hot);


	return ret;
}