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
struct vnet_port {int /*<<< orphan*/  q_index; } ;
struct netdev_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VNET_PORT_TO_NET_DEVICE (struct vnet_port*) ; 
 int /*<<< orphan*/  __netif_tx_lock (struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __netif_tx_unlock (struct netdev_queue*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void maybe_tx_wakeup(struct vnet_port *port)
{
	struct netdev_queue *txq;

	txq = netdev_get_tx_queue(VNET_PORT_TO_NET_DEVICE(port),
				  port->q_index);
	__netif_tx_lock(txq, smp_processor_id());
	if (likely(netif_tx_queue_stopped(txq)))
		netif_tx_wake_queue(txq);
	__netif_tx_unlock(txq);
}