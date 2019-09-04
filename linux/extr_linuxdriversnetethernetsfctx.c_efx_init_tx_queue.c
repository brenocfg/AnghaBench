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
struct efx_tx_queue {int empty_read_count; int xmit_more_available; int timestamping; scalar_t__ channel; int initialised; int /*<<< orphan*/  handle_tso; scalar_t__ completed_timestamp_minor; scalar_t__ completed_timestamp_major; int /*<<< orphan*/  ptr_mask; int /*<<< orphan*/  completed_desc_ptr; scalar_t__ old_read_count; scalar_t__ read_count; scalar_t__ old_write_count; scalar_t__ packet_write_count; scalar_t__ write_count; scalar_t__ insert_count; int /*<<< orphan*/  queue; struct efx_nic* efx; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int EFX_EMPTY_COUNT_VALID ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_enqueue_skb_tso ; 
 int /*<<< orphan*/  efx_nic_init_tx (struct efx_tx_queue*) ; 
 scalar_t__ efx_ptp_channel (struct efx_nic*) ; 
 scalar_t__ efx_ptp_use_mac_tx_timestamps (struct efx_nic*) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void efx_init_tx_queue(struct efx_tx_queue *tx_queue)
{
	struct efx_nic *efx = tx_queue->efx;

	netif_dbg(efx, drv, efx->net_dev,
		  "initialising TX queue %d\n", tx_queue->queue);

	tx_queue->insert_count = 0;
	tx_queue->write_count = 0;
	tx_queue->packet_write_count = 0;
	tx_queue->old_write_count = 0;
	tx_queue->read_count = 0;
	tx_queue->old_read_count = 0;
	tx_queue->empty_read_count = 0 | EFX_EMPTY_COUNT_VALID;
	tx_queue->xmit_more_available = false;
	tx_queue->timestamping = (efx_ptp_use_mac_tx_timestamps(efx) &&
				  tx_queue->channel == efx_ptp_channel(efx));
	tx_queue->completed_desc_ptr = tx_queue->ptr_mask;
	tx_queue->completed_timestamp_major = 0;
	tx_queue->completed_timestamp_minor = 0;

	/* Set up default function pointers. These may get replaced by
	 * efx_nic_init_tx() based off NIC/queue capabilities.
	 */
	tx_queue->handle_tso = efx_enqueue_skb_tso;

	/* Set up TX descriptor ring */
	efx_nic_init_tx(tx_queue);

	tx_queue->initialised = true;
}