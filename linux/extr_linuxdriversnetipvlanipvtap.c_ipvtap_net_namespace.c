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
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 void const* dev_net (struct net_device*) ; 
 struct net_device* to_net_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const void *ipvtap_net_namespace(struct device *d)
{
	struct net_device *dev = to_net_dev(d->parent);
	return dev_net(dev);
}