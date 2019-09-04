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
struct ef4_rx_queue {int /*<<< orphan*/ * buffer; TYPE_1__* efx; } ;
struct TYPE_2__ {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  ef4_nic_remove_rx (struct ef4_rx_queue*) ; 
 int /*<<< orphan*/  ef4_rx_queue_index (struct ef4_rx_queue*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_dbg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void ef4_remove_rx_queue(struct ef4_rx_queue *rx_queue)
{
	netif_dbg(rx_queue->efx, drv, rx_queue->efx->net_dev,
		  "destroying RX queue %d\n", ef4_rx_queue_index(rx_queue));

	ef4_nic_remove_rx(rx_queue);

	kfree(rx_queue->buffer);
	rx_queue->buffer = NULL;
}