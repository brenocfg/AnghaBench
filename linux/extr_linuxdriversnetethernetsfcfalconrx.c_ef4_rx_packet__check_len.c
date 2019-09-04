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
struct ef4_rx_queue {struct ef4_nic* efx; } ;
struct ef4_rx_buffer {int len; int /*<<< orphan*/  flags; } ;
struct ef4_nic {int /*<<< orphan*/  net_dev; TYPE_1__* type; } ;
struct TYPE_4__ {int /*<<< orphan*/  n_rx_overlength; } ;
struct TYPE_3__ {unsigned int rx_buffer_padding; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_RX_PKT_DISCARD ; 
 scalar_t__ EF4_WORKAROUND_8071 (struct ef4_nic*) ; 
 int /*<<< orphan*/  RESET_TYPE_RX_RECOVERY ; 
 TYPE_2__* ef4_rx_queue_channel (struct ef4_rx_queue*) ; 
 int /*<<< orphan*/  ef4_rx_queue_index (struct ef4_rx_queue*) ; 
 int /*<<< orphan*/  ef4_schedule_reset (struct ef4_nic*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netif_err (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,unsigned int,...) ; 
 int /*<<< orphan*/  rx_err ; 

__attribute__((used)) static void ef4_rx_packet__check_len(struct ef4_rx_queue *rx_queue,
				     struct ef4_rx_buffer *rx_buf,
				     int len)
{
	struct ef4_nic *efx = rx_queue->efx;
	unsigned max_len = rx_buf->len - efx->type->rx_buffer_padding;

	if (likely(len <= max_len))
		return;

	/* The packet must be discarded, but this is only a fatal error
	 * if the caller indicated it was
	 */
	rx_buf->flags |= EF4_RX_PKT_DISCARD;

	if ((len > rx_buf->len) && EF4_WORKAROUND_8071(efx)) {
		if (net_ratelimit())
			netif_err(efx, rx_err, efx->net_dev,
				  " RX queue %d seriously overlength "
				  "RX event (0x%x > 0x%x+0x%x). Leaking\n",
				  ef4_rx_queue_index(rx_queue), len, max_len,
				  efx->type->rx_buffer_padding);
		ef4_schedule_reset(efx, RESET_TYPE_RX_RECOVERY);
	} else {
		if (net_ratelimit())
			netif_err(efx, rx_err, efx->net_dev,
				  " RX queue %d overlength RX event "
				  "(0x%x > 0x%x)\n",
				  ef4_rx_queue_index(rx_queue), len, max_len);
	}

	ef4_rx_queue_channel(rx_queue)->n_rx_overlength++;
}