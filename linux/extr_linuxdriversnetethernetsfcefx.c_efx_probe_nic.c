#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rx_hash_key; } ;
struct efx_nic {int n_channels; TYPE_1__* type; int /*<<< orphan*/  timer_quantum_ns; int /*<<< orphan*/  irq_mod_step_us; int /*<<< orphan*/  n_rx_channels; int /*<<< orphan*/  net_dev; int /*<<< orphan*/  n_tx_channels; TYPE_2__ rss_context; int /*<<< orphan*/  max_tx_channels; int /*<<< orphan*/  max_channels; } ;
struct TYPE_3__ {int (* probe ) (struct efx_nic*) ;int (* dimension_resources ) (struct efx_nic*) ;int /*<<< orphan*/  (* remove ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int EAGAIN ; 
 int ENOSPC ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_init_irq_moderation (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int efx_probe_interrupts (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_remove_interrupts (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_set_channels (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_set_default_rx_indir_table (struct efx_nic*,TYPE_2__*) ; 
 int /*<<< orphan*/  netdev_rss_key_fill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_set_real_num_rx_queues (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  rx_irq_mod_usec ; 
 int stub1 (struct efx_nic*) ; 
 int stub2 (struct efx_nic*) ; 
 int /*<<< orphan*/  stub3 (struct efx_nic*) ; 
 int /*<<< orphan*/  tx_irq_mod_usec ; 

__attribute__((used)) static int efx_probe_nic(struct efx_nic *efx)
{
	int rc;

	netif_dbg(efx, probe, efx->net_dev, "creating NIC\n");

	/* Carry out hardware-type specific initialisation */
	rc = efx->type->probe(efx);
	if (rc)
		return rc;

	do {
		if (!efx->max_channels || !efx->max_tx_channels) {
			netif_err(efx, drv, efx->net_dev,
				  "Insufficient resources to allocate"
				  " any channels\n");
			rc = -ENOSPC;
			goto fail1;
		}

		/* Determine the number of channels and queues by trying
		 * to hook in MSI-X interrupts.
		 */
		rc = efx_probe_interrupts(efx);
		if (rc)
			goto fail1;

		efx_set_channels(efx);

		/* dimension_resources can fail with EAGAIN */
		rc = efx->type->dimension_resources(efx);
		if (rc != 0 && rc != -EAGAIN)
			goto fail2;

		if (rc == -EAGAIN)
			/* try again with new max_channels */
			efx_remove_interrupts(efx);

	} while (rc == -EAGAIN);

	if (efx->n_channels > 1)
		netdev_rss_key_fill(efx->rss_context.rx_hash_key,
				    sizeof(efx->rss_context.rx_hash_key));
	efx_set_default_rx_indir_table(efx, &efx->rss_context);

	netif_set_real_num_tx_queues(efx->net_dev, efx->n_tx_channels);
	netif_set_real_num_rx_queues(efx->net_dev, efx->n_rx_channels);

	/* Initialise the interrupt moderation settings */
	efx->irq_mod_step_us = DIV_ROUND_UP(efx->timer_quantum_ns, 1000);
	efx_init_irq_moderation(efx, tx_irq_mod_usec, rx_irq_mod_usec, true,
				true);

	return 0;

fail2:
	efx_remove_interrupts(efx);
fail1:
	efx->type->remove(efx);
	return rc;
}