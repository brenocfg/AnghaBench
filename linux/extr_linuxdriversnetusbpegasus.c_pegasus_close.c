#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  rx_tl; } ;
typedef  TYPE_1__ pegasus_t ;

/* Variables and functions */
 int PEGASUS_UNPLUG ; 
 int /*<<< orphan*/  disable_net_traffic (TYPE_1__*) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink_all_urbs (TYPE_1__*) ; 

__attribute__((used)) static int pegasus_close(struct net_device *net)
{
	pegasus_t *pegasus = netdev_priv(net);

	netif_stop_queue(net);
	if (!(pegasus->flags & PEGASUS_UNPLUG))
		disable_net_traffic(pegasus);
	tasklet_kill(&pegasus->rx_tl);
	unlink_all_urbs(pegasus);

	return 0;
}