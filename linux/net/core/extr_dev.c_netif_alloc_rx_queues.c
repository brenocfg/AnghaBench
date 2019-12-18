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
struct netdev_rx_queue {int /*<<< orphan*/  xdp_rxq; struct net_device* dev; } ;
struct net_device {unsigned int num_rx_queues; struct netdev_rx_queue* _rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int __GFP_RETRY_MAYFAIL ; 
 int /*<<< orphan*/  kvfree (struct netdev_rx_queue*) ; 
 struct netdev_rx_queue* kvzalloc (size_t,int) ; 
 int xdp_rxq_info_reg (int /*<<< orphan*/ *,struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netif_alloc_rx_queues(struct net_device *dev)
{
	unsigned int i, count = dev->num_rx_queues;
	struct netdev_rx_queue *rx;
	size_t sz = count * sizeof(*rx);
	int err = 0;

	BUG_ON(count < 1);

	rx = kvzalloc(sz, GFP_KERNEL | __GFP_RETRY_MAYFAIL);
	if (!rx)
		return -ENOMEM;

	dev->_rx = rx;

	for (i = 0; i < count; i++) {
		rx[i].dev = dev;

		/* XDP RX-queue setup */
		err = xdp_rxq_info_reg(&rx[i].xdp_rxq, dev, i);
		if (err < 0)
			goto err_rxq_info;
	}
	return 0;

err_rxq_info:
	/* Rollback successful reg's and free other resources */
	while (i--)
		xdp_rxq_info_unreg(&rx[i].xdp_rxq);
	kvfree(dev->_rx);
	dev->_rx = NULL;
	return err;
}