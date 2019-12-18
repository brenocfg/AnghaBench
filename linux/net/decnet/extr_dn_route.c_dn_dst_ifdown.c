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
struct neighbour {struct net_device* dev; } ;
struct dst_entry {int dummy; } ;
struct dn_route {struct neighbour* n; } ;
struct TYPE_2__ {struct net_device* loopback_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 TYPE_1__* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 

__attribute__((used)) static void dn_dst_ifdown(struct dst_entry *dst, struct net_device *dev, int how)
{
	if (how) {
		struct dn_route *rt = (struct dn_route *) dst;
		struct neighbour *n = rt->n;

		if (n && n->dev == dev) {
			n->dev = dev_net(dev)->loopback_dev;
			dev_hold(n->dev);
			dev_put(dev);
		}
	}
}