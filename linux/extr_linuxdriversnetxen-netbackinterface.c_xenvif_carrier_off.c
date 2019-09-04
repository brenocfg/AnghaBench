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
struct xenvif {int /*<<< orphan*/  status; struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIF_STATUS_CONNECTED ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenvif_down (struct xenvif*) ; 

void xenvif_carrier_off(struct xenvif *vif)
{
	struct net_device *dev = vif->dev;

	rtnl_lock();
	if (test_and_clear_bit(VIF_STATUS_CONNECTED, &vif->status)) {
		netif_carrier_off(dev); /* discard queued packets */
		if (netif_running(dev))
			xenvif_down(vif);
	}
	rtnl_unlock();
}