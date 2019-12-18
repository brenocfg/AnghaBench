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
struct net_device {unsigned int num_rx_queues; TYPE_1__* _rx; } ;
struct TYPE_2__ {int /*<<< orphan*/  xdp_rxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (TYPE_1__*) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netif_free_rx_queues(struct net_device *dev)
{
	unsigned int i, count = dev->num_rx_queues;

	/* netif_alloc_rx_queues alloc failed, resources have been unreg'ed */
	if (!dev->_rx)
		return;

	for (i = 0; i < count; i++)
		xdp_rxq_info_unreg(&dev->_rx[i].xdp_rxq);

	kvfree(dev->_rx);
}