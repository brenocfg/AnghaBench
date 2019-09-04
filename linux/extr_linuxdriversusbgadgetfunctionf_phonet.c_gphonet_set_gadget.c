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
struct usb_gadget {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 

void gphonet_set_gadget(struct net_device *net, struct usb_gadget *g)
{
	SET_NETDEV_DEV(net, &g->dev);
}