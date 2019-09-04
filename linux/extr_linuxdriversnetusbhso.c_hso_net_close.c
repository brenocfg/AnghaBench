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
struct hso_net {int /*<<< orphan*/  parent; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSO_NET_RUNNING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hso_stop_net_device (int /*<<< orphan*/ ) ; 
 struct hso_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int hso_net_close(struct net_device *net)
{
	struct hso_net *odev = netdev_priv(net);

	/* we don't need the queue anymore */
	netif_stop_queue(net);
	/* no longer running */
	clear_bit(HSO_NET_RUNNING, &odev->flags);

	hso_stop_net_device(odev->parent);

	/* done */
	return 0;
}