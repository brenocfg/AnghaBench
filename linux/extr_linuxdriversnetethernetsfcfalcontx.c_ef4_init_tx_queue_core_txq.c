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
struct ef4_tx_queue {int queue; int /*<<< orphan*/  core_txq; struct ef4_nic* efx; } ;
struct ef4_nic {int n_tx_channels; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int EF4_TXQ_TYPES ; 
 int EF4_TXQ_TYPE_HIGHPRI ; 
 int /*<<< orphan*/  netdev_get_tx_queue (int /*<<< orphan*/ ,int) ; 

void ef4_init_tx_queue_core_txq(struct ef4_tx_queue *tx_queue)
{
	struct ef4_nic *efx = tx_queue->efx;

	/* Must be inverse of queue lookup in ef4_hard_start_xmit() */
	tx_queue->core_txq =
		netdev_get_tx_queue(efx->net_dev,
				    tx_queue->queue / EF4_TXQ_TYPES +
				    ((tx_queue->queue & EF4_TXQ_TYPE_HIGHPRI) ?
				     efx->n_tx_channels : 0));
}