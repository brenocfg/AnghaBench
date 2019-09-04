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
struct ipheth_device {int /*<<< orphan*/  carrier_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct ipheth_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int ipheth_close(struct net_device *net)
{
	struct ipheth_device *dev = netdev_priv(net);

	cancel_delayed_work_sync(&dev->carrier_work);
	netif_stop_queue(net);
	return 0;
}