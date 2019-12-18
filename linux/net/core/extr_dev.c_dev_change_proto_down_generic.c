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
struct net_device {int proto_down; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 

int dev_change_proto_down_generic(struct net_device *dev, bool proto_down)
{
	if (proto_down)
		netif_carrier_off(dev);
	else
		netif_carrier_on(dev);
	dev->proto_down = proto_down;
	return 0;
}