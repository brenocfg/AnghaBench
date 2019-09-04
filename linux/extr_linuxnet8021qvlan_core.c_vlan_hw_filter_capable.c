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
struct net_device {int features; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021AD ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_STAG_FILTER ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vlan_hw_filter_capable(const struct net_device *dev, __be16 proto)
{
	if (proto == htons(ETH_P_8021Q) &&
	    dev->features & NETIF_F_HW_VLAN_CTAG_FILTER)
		return true;
	if (proto == htons(ETH_P_8021AD) &&
	    dev->features & NETIF_F_HW_VLAN_STAG_FILTER)
		return true;
	return false;
}