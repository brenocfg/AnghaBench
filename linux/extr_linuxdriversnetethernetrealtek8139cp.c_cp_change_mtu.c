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
struct net_device {int mtu; } ;
struct cp_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cp_close (struct net_device*) ; 
 int cp_open (struct net_device*) ; 
 int /*<<< orphan*/  cp_set_rxbufsize (struct cp_private*) ; 
 struct cp_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static int cp_change_mtu(struct net_device *dev, int new_mtu)
{
	struct cp_private *cp = netdev_priv(dev);

	/* if network interface not up, no need for complexity */
	if (!netif_running(dev)) {
		dev->mtu = new_mtu;
		cp_set_rxbufsize(cp);	/* set new rx buf size */
		return 0;
	}

	/* network IS up, close it, reset MTU, and come up again. */
	cp_close(dev);
	dev->mtu = new_mtu;
	cp_set_rxbufsize(cp);
	return cp_open(dev);
}