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
struct net_device {int flags; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int /*<<< orphan*/  dev_set_allmulti (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_set_promiscuity (struct net_device*,int) ; 
 struct net_device* dsa_slave_to_master (struct net_device*) ; 

__attribute__((used)) static void dsa_slave_change_rx_flags(struct net_device *dev, int change)
{
	struct net_device *master = dsa_slave_to_master(dev);
	if (dev->flags & IFF_UP) {
		if (change & IFF_ALLMULTI)
			dev_set_allmulti(master,
					 dev->flags & IFF_ALLMULTI ? 1 : -1);
		if (change & IFF_PROMISC)
			dev_set_promiscuity(master,
					    dev->flags & IFF_PROMISC ? 1 : -1);
	}
}