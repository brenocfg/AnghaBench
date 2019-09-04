#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;
struct ipvl_dev {int dummy; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_address; TYPE_1__* ifa_dev; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct TYPE_2__ {scalar_t__ dev; } ;

/* Variables and functions */
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  ipvlan_add_addr4 (struct ipvl_dev*,struct in_addr*) ; 
 int /*<<< orphan*/  ipvlan_del_addr4 (struct ipvl_dev*,struct in_addr*) ; 
 int /*<<< orphan*/  ipvlan_is_valid_dev (struct net_device*) ; 
 struct ipvl_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ipvlan_addr4_event(struct notifier_block *unused,
			      unsigned long event, void *ptr)
{
	struct in_ifaddr *if4 = (struct in_ifaddr *)ptr;
	struct net_device *dev = (struct net_device *)if4->ifa_dev->dev;
	struct ipvl_dev *ipvlan = netdev_priv(dev);
	struct in_addr ip4_addr;

	if (!ipvlan_is_valid_dev(dev))
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		ip4_addr.s_addr = if4->ifa_address;
		if (ipvlan_add_addr4(ipvlan, &ip4_addr))
			return NOTIFY_BAD;
		break;

	case NETDEV_DOWN:
		ip4_addr.s_addr = if4->ifa_address;
		ipvlan_del_addr4(ipvlan, &ip4_addr);
		break;
	}

	return NOTIFY_OK;
}