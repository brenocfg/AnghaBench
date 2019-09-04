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
struct efx_rx_queue {struct efx_nic* efx; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESET_TYPE_DISABLE ; 
 int /*<<< orphan*/  efx_rx_queue_index (struct efx_rx_queue*) ; 
 int /*<<< orphan*/  efx_schedule_reset (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_info (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void efx_ef10_handle_rx_wrong_queue(struct efx_rx_queue *rx_queue,
					   unsigned int rx_queue_label)
{
	struct efx_nic *efx = rx_queue->efx;

	netif_info(efx, hw, efx->net_dev,
		   "rx event arrived on queue %d labeled as queue %u\n",
		   efx_rx_queue_index(rx_queue), rx_queue_label);

	efx_schedule_reset(efx, RESET_TYPE_DISABLE);
}