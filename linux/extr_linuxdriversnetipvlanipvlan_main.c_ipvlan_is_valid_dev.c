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
struct ipvl_dev {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 struct ipvl_dev* netdev_priv (struct net_device const*) ; 
 int /*<<< orphan*/  netif_is_ipvlan (struct net_device const*) ; 

__attribute__((used)) static bool ipvlan_is_valid_dev(const struct net_device *dev)
{
	struct ipvl_dev *ipvlan = netdev_priv(dev);

	if (!netif_is_ipvlan(dev))
		return false;

	if (!ipvlan || !ipvlan->port)
		return false;

	return true;
}