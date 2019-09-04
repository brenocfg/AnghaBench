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
struct net_device {int flags; scalar_t__ type; scalar_t__ addr_len; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 scalar_t__ ETH_ALEN ; 
 int IFF_LOOPBACK ; 
 scalar_t__ batadv_is_on_batman_iface (struct net_device const*) ; 

__attribute__((used)) static bool batadv_is_valid_iface(const struct net_device *net_dev)
{
	if (net_dev->flags & IFF_LOOPBACK)
		return false;

	if (net_dev->type != ARPHRD_ETHER)
		return false;

	if (net_dev->addr_len != ETH_ALEN)
		return false;

	/* no batman over batman */
	if (batadv_is_on_batman_iface(net_dev))
		return false;

	return true;
}