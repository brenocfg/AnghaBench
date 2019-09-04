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
struct net_device {scalar_t__ operstate; } ;

/* Variables and functions */
 scalar_t__ IF_OPER_DORMANT ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device const*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_dormant_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_dormant_on (struct net_device*) ; 

void netif_stacked_transfer_operstate(const struct net_device *rootdev,
					struct net_device *dev)
{
	if (rootdev->operstate == IF_OPER_DORMANT)
		netif_dormant_on(dev);
	else
		netif_dormant_off(dev);

	if (netif_carrier_ok(rootdev))
		netif_carrier_on(dev);
	else
		netif_carrier_off(dev);
}