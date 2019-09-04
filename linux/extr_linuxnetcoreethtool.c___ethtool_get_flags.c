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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_FLAG_LRO ; 
 int /*<<< orphan*/  ETH_FLAG_NTUPLE ; 
 int /*<<< orphan*/  ETH_FLAG_RXHASH ; 
 int /*<<< orphan*/  ETH_FLAG_RXVLAN ; 
 int /*<<< orphan*/  ETH_FLAG_TXVLAN ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int NETIF_F_LRO ; 
 int NETIF_F_NTUPLE ; 
 int NETIF_F_RXHASH ; 

__attribute__((used)) static u32 __ethtool_get_flags(struct net_device *dev)
{
	u32 flags = 0;

	if (dev->features & NETIF_F_LRO)
		flags |= ETH_FLAG_LRO;
	if (dev->features & NETIF_F_HW_VLAN_CTAG_RX)
		flags |= ETH_FLAG_RXVLAN;
	if (dev->features & NETIF_F_HW_VLAN_CTAG_TX)
		flags |= ETH_FLAG_TXVLAN;
	if (dev->features & NETIF_F_NTUPLE)
		flags |= ETH_FLAG_NTUPLE;
	if (dev->features & NETIF_F_RXHASH)
		flags |= ETH_FLAG_RXHASH;

	return flags;
}