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
struct net_device {int dummy; } ;
struct dst_entry {struct net_device* dev; scalar_t__ xfrm; } ;
struct TYPE_2__ {struct net_device* loopback_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 TYPE_1__* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct dst_entry* xfrm_dst_child (struct dst_entry*) ; 

void xfrm_dst_ifdown(struct dst_entry *dst, struct net_device *dev)
{
	while ((dst = xfrm_dst_child(dst)) && dst->xfrm && dst->dev == dev) {
		dst->dev = dev_net(dev)->loopback_dev;
		dev_hold(dst->dev);
		dev_put(dev);
	}
}