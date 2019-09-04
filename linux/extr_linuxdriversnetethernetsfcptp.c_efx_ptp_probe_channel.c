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
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
struct TYPE_2__ {scalar_t__ core_index; } ;
struct efx_channel {TYPE_1__ rx_queue; scalar_t__ irq_moderation_us; struct efx_nic* efx; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  drv ; 
 int efx_ptp_probe (struct efx_nic*,struct efx_channel*) ; 
 int /*<<< orphan*/  netif_warn (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int efx_ptp_probe_channel(struct efx_channel *channel)
{
	struct efx_nic *efx = channel->efx;
	int rc;

	channel->irq_moderation_us = 0;
	channel->rx_queue.core_index = 0;

	rc = efx_ptp_probe(efx, channel);
	/* Failure to probe PTP is not fatal; this channel will just not be
	 * used for anything.
	 * In the case of EPERM, efx_ptp_probe will print its own message (in
	 * efx_ptp_get_attributes()), so we don't need to.
	 */
	if (rc && rc != -EPERM)
		netif_warn(efx, drv, efx->net_dev,
			   "Failed to probe PTP, rc=%d\n", rc);
	return 0;
}