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
struct pcmcia_device {scalar_t__ open; struct net_device* priv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  wl3501_close (struct net_device*) ; 
 int /*<<< orphan*/  wl3501_release (struct pcmcia_device*) ; 

__attribute__((used)) static void wl3501_detach(struct pcmcia_device *link)
{
	struct net_device *dev = link->priv;

	/* If the device is currently configured and active, we won't actually
	 * delete it yet.  Instead, it is marked so that when the release()
	 * function is called, that will trigger a proper detach(). */

	while (link->open > 0)
		wl3501_close(dev);

	netif_device_detach(dev);
	wl3501_release(link);

	unregister_netdev(dev);

	if (link->priv)
		free_netdev(link->priv);
}