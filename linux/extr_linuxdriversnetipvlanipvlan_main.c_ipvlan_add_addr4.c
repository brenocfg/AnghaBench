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
struct ipvl_dev {int /*<<< orphan*/  addrs_lock; TYPE_1__* dev; int /*<<< orphan*/  port; } ;
struct in_addr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ifup ; 
 int ipvlan_add_addr (struct ipvl_dev*,struct in_addr*,int) ; 
 scalar_t__ ipvlan_addr_busy (int /*<<< orphan*/ ,struct in_addr*,int) ; 
 int /*<<< orphan*/  netif_err (struct ipvl_dev*,int /*<<< orphan*/ ,TYPE_1__*,char*,struct in_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipvlan_add_addr4(struct ipvl_dev *ipvlan, struct in_addr *ip4_addr)
{
	int ret = -EINVAL;

	spin_lock_bh(&ipvlan->addrs_lock);
	if (ipvlan_addr_busy(ipvlan->port, ip4_addr, false))
		netif_err(ipvlan, ifup, ipvlan->dev,
			  "Failed to add IPv4=%pI4 on %s intf.\n",
			  ip4_addr, ipvlan->dev->name);
	else
		ret = ipvlan_add_addr(ipvlan, ip4_addr, false);
	spin_unlock_bh(&ipvlan->addrs_lock);
	return ret;
}