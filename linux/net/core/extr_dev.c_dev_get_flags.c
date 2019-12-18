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
struct net_device {unsigned int flags; unsigned int gflags; } ;

/* Variables and functions */
 unsigned int IFF_ALLMULTI ; 
 unsigned int IFF_DORMANT ; 
 unsigned int IFF_LOWER_UP ; 
 unsigned int IFF_PROMISC ; 
 unsigned int IFF_RUNNING ; 
 scalar_t__ netif_carrier_ok (struct net_device const*) ; 
 scalar_t__ netif_dormant (struct net_device const*) ; 
 scalar_t__ netif_oper_up (struct net_device const*) ; 
 scalar_t__ netif_running (struct net_device const*) ; 

unsigned int dev_get_flags(const struct net_device *dev)
{
	unsigned int flags;

	flags = (dev->flags & ~(IFF_PROMISC |
				IFF_ALLMULTI |
				IFF_RUNNING |
				IFF_LOWER_UP |
				IFF_DORMANT)) |
		(dev->gflags & (IFF_PROMISC |
				IFF_ALLMULTI));

	if (netif_running(dev)) {
		if (netif_oper_up(dev))
			flags |= IFF_RUNNING;
		if (netif_carrier_ok(dev))
			flags |= IFF_LOWER_UP;
		if (netif_dormant(dev))
			flags |= IFF_DORMANT;
	}

	return flags;
}