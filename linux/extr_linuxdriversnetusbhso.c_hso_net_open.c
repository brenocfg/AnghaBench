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
struct net_device {int /*<<< orphan*/  dev; } ;
struct iphdr {int dummy; } ;
struct hso_net {int rx_buf_missing; int /*<<< orphan*/  parent; int /*<<< orphan*/  flags; int /*<<< orphan*/  net_lock; scalar_t__ rx_buf_size; int /*<<< orphan*/  rx_parse_state; int /*<<< orphan*/ * skb_tx_buf; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HSO_NET_RUNNING ; 
 int /*<<< orphan*/  WAIT_IP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hso_start_net_device (int /*<<< orphan*/ ) ; 
 struct hso_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hso_net_open(struct net_device *net)
{
	struct hso_net *odev = netdev_priv(net);
	unsigned long flags = 0;

	if (!odev) {
		dev_err(&net->dev, "No net device !\n");
		return -ENODEV;
	}

	odev->skb_tx_buf = NULL;

	/* setup environment */
	spin_lock_irqsave(&odev->net_lock, flags);
	odev->rx_parse_state = WAIT_IP;
	odev->rx_buf_size = 0;
	odev->rx_buf_missing = sizeof(struct iphdr);
	spin_unlock_irqrestore(&odev->net_lock, flags);

	/* We are up and running. */
	set_bit(HSO_NET_RUNNING, &odev->flags);
	hso_start_net_device(odev->parent);

	/* Tell the kernel we are ready to start receiving from it */
	netif_start_queue(net);

	return 0;
}