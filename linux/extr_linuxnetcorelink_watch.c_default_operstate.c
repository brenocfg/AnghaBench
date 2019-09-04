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
struct net_device {scalar_t__ ifindex; } ;

/* Variables and functions */
 unsigned char IF_OPER_DORMANT ; 
 unsigned char IF_OPER_DOWN ; 
 unsigned char IF_OPER_LOWERLAYERDOWN ; 
 unsigned char IF_OPER_UP ; 
 scalar_t__ dev_get_iflink (struct net_device const*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device const*) ; 
 scalar_t__ netif_dormant (struct net_device const*) ; 

__attribute__((used)) static unsigned char default_operstate(const struct net_device *dev)
{
	if (!netif_carrier_ok(dev))
		return (dev->ifindex != dev_get_iflink(dev) ?
			IF_OPER_LOWERLAYERDOWN : IF_OPER_DOWN);

	if (netif_dormant(dev))
		return IF_OPER_DORMANT;

	return IF_OPER_UP;
}