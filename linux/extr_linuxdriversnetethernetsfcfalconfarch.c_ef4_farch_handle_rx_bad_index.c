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
struct ef4_rx_queue {int scatter_n; int removed_count; int ptr_mask; struct ef4_nic* efx; } ;
struct ef4_nic {int /*<<< orphan*/  net_dev; } ;
struct ef4_channel {int /*<<< orphan*/  n_rx_nodesc_trunc; } ;

/* Variables and functions */
 scalar_t__ EF4_WORKAROUND_5676 (struct ef4_nic*) ; 
 int /*<<< orphan*/  RESET_TYPE_DISABLE ; 
 int /*<<< orphan*/  RESET_TYPE_RX_RECOVERY ; 
 struct ef4_channel* ef4_rx_queue_channel (struct ef4_rx_queue*) ; 
 int /*<<< orphan*/  ef4_schedule_reset (struct ef4_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_info (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rx_err ; 

__attribute__((used)) static bool
ef4_farch_handle_rx_bad_index(struct ef4_rx_queue *rx_queue, unsigned index)
{
	struct ef4_channel *channel = ef4_rx_queue_channel(rx_queue);
	struct ef4_nic *efx = rx_queue->efx;
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

	ef4_schedule_reset(efx, EF4_WORKAROUND_5676(efx) ?
			   RESET_TYPE_RX_RECOVERY : RESET_TYPE_DISABLE);
	return false;
}