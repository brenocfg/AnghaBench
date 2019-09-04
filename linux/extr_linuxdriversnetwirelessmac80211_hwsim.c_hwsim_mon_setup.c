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
struct net_device {int needs_free_netdev; int* dev_addr; int /*<<< orphan*/  type; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IEEE80211_RADIOTAP ; 
 int /*<<< orphan*/  IFF_NO_QUEUE ; 
 int /*<<< orphan*/  eth_zero_addr (int*) ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  hwsim_netdev_ops ; 

__attribute__((used)) static void hwsim_mon_setup(struct net_device *dev)
{
	dev->netdev_ops = &hwsim_netdev_ops;
	dev->needs_free_netdev = true;
	ether_setup(dev);
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->type = ARPHRD_IEEE80211_RADIOTAP;
	eth_zero_addr(dev->dev_addr);
	dev->dev_addr[0] = 0x12;
}