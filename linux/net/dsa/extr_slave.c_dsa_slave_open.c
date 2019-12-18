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
struct net_device {int flags; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  phydev; } ;
struct dsa_port {int /*<<< orphan*/  pl; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int dev_set_allmulti (struct net_device*,int) ; 
 int dev_set_promiscuity (struct net_device*,int) ; 
 int dev_uc_add (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_uc_del (struct net_device*,int /*<<< orphan*/ ) ; 
 int dsa_port_enable (struct dsa_port*,int /*<<< orphan*/ ) ; 
 struct net_device* dsa_slave_to_master (struct net_device*) ; 
 struct dsa_port* dsa_slave_to_port (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_slave_open(struct net_device *dev)
{
	struct net_device *master = dsa_slave_to_master(dev);
	struct dsa_port *dp = dsa_slave_to_port(dev);
	int err;

	if (!(master->flags & IFF_UP))
		return -ENETDOWN;

	if (!ether_addr_equal(dev->dev_addr, master->dev_addr)) {
		err = dev_uc_add(master, dev->dev_addr);
		if (err < 0)
			goto out;
	}

	if (dev->flags & IFF_ALLMULTI) {
		err = dev_set_allmulti(master, 1);
		if (err < 0)
			goto del_unicast;
	}
	if (dev->flags & IFF_PROMISC) {
		err = dev_set_promiscuity(master, 1);
		if (err < 0)
			goto clear_allmulti;
	}

	err = dsa_port_enable(dp, dev->phydev);
	if (err)
		goto clear_promisc;

	phylink_start(dp->pl);

	return 0;

clear_promisc:
	if (dev->flags & IFF_PROMISC)
		dev_set_promiscuity(master, -1);
clear_allmulti:
	if (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(master, -1);
del_unicast:
	if (!ether_addr_equal(dev->dev_addr, master->dev_addr))
		dev_uc_del(master, dev->dev_addr);
out:
	return err;
}