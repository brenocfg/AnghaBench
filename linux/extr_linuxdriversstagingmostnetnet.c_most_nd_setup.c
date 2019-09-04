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
struct net_device {int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  most_nd_ops ; 

__attribute__((used)) static void most_nd_setup(struct net_device *dev)
{
	ether_setup(dev);
	dev->netdev_ops = &most_nd_ops;
}