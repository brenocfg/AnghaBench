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
struct efx_rx_queue {int scatter_n; int removed_count; int ptr_mask; struct efx_nic* efx; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
struct efx_channel {int /*<<< orphan*/  n_rx_nodesc_trunc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESET_TYPE_DISABLE ; 
 struct efx_channel* efx_rx_queue_channel (struct efx_rx_queue*) ; 
 int /*<<< orphan*/  efx_schedule_reset (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rx_err ; 

__attribute__((used)) static bool
efx_farch_handle_rx_bad_index(struct efx_rx_queue *rx_queue, unsigned index)
{
	struct efx_channel *channel = efx_rx_queue_channel(rx_queue);
	struct efx_nic *efx = rx_queue->efx;
	unsigned expected, dropped;

	if (rx_queue->scatter_n &&
	    index == ((rx_queue->removed_count + rx_queue->scatter_n - 1) &
		      rx_queue->ptr_mask)) {
		++channel->n_rx_nodesc_trunc;
		return true;
	}

	expected = rx_queue->removed_count & rx_queue->ptr_mask;
	dropped = (index - expected) & rx_queue->ptr_mask;
	netif_info(efx, rx_err, efx->net_dev,
		   "dropped %d events (index=%d expected=%d)\n",
		   dropped, index, expected);

	efx_schedule_reset(efx, RESET_TYPE_DISABLE);
	return false;
}