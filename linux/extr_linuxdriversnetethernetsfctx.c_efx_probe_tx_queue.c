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
struct efx_tx_queue {unsigned int ptr_mask; int /*<<< orphan*/ * buffer; int /*<<< orphan*/ * cb_page; int /*<<< orphan*/  queue; struct efx_nic* efx; } ;
struct efx_nic {int /*<<< orphan*/  txq_entries; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 unsigned int EFX_MAX_DMAQ_SIZE ; 
 int /*<<< orphan*/  EFX_MIN_DMAQ_SIZE ; 
 int /*<<< orphan*/  EFX_WARN_ON_PARANOID (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int efx_nic_probe_tx (struct efx_tx_queue*) ; 
 unsigned int efx_tx_cb_page_count (struct efx_tx_queue*) ; 
 void* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 unsigned int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  roundup_pow_of_two (int /*<<< orphan*/ ) ; 

int efx_probe_tx_queue(struct efx_tx_queue *tx_queue)
{
	struct efx_nic *efx = tx_queue->efx;
	unsigned int entries;
	int rc;

	/* Create the smallest power-of-two aligned ring */
	entries = max(roundup_pow_of_two(efx->txq_entries), EFX_MIN_DMAQ_SIZE);
	EFX_WARN_ON_PARANOID(entries > EFX_MAX_DMAQ_SIZE);
	tx_queue->ptr_mask = entries - 1;

	netif_dbg(efx, probe, efx->net_dev,
		  "creating TX queue %d size %#x mask %#x\n",
		  tx_queue->queue, efx->txq_entries, tx_queue->ptr_mask);

	/* Allocate software ring */
	tx_queue->buffer = kcalloc(entries, sizeof(*tx_queue->buffer),
				   GFP_KERNEL);
	if (!tx_queue->buffer)
		return -ENOMEM;

	tx_queue->cb_page = kcalloc(efx_tx_cb_page_count(tx_queue),
				    sizeof(tx_queue->cb_page[0]), GFP_KERNEL);
	if (!tx_queue->cb_page) {
		rc = -ENOMEM;
		goto fail1;
	}

	/* Allocate hardware ring */
	rc = efx_nic_probe_tx(tx_queue);
	if (rc)
		goto fail2;

	return 0;

fail2:
	kfree(tx_queue->cb_page);
	tx_queue->cb_page = NULL;
fail1:
	kfree(tx_queue->buffer);
	tx_queue->buffer = NULL;
	return rc;
}