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
typedef  int u32 ;
struct usbnet {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ link_up; } ;

/* Variables and functions */
 struct usbnet* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 TYPE_1__* sierra_net_get_private (struct usbnet*) ; 

__attribute__((used)) static u32 sierra_net_get_link(struct net_device *net)
{
	struct usbnet *dev = netdev_priv(net);
	/* Report link is down whenever the interface is down */
	return sierra_net_get_private(dev)->link_up && netif_running(net);
}