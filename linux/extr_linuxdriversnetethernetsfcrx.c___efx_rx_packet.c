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
typedef  int /*<<< orphan*/  u8 ;
struct efx_rx_queue {int dummy; } ;
struct efx_rx_buffer {int flags; int /*<<< orphan*/  len; } ;
struct efx_nic {int rx_packet_len_offset; int loopback_selftest; TYPE_1__* net_dev; } ;
struct efx_channel {int /*<<< orphan*/  rx_pkt_n_frags; TYPE_2__* type; int /*<<< orphan*/  rx_pkt_index; int /*<<< orphan*/  rx_queue; struct efx_nic* efx; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_4__ {int /*<<< orphan*/  receive_skb; } ;
struct TYPE_3__ {int features; } ;

/* Variables and functions */
 int EFX_RX_PKT_CSUMMED ; 
 int EFX_RX_PKT_PREFIX_LEN ; 
 int EFX_RX_PKT_TCP ; 
 int NETIF_F_RXCSUM ; 
 struct efx_rx_queue* efx_channel_get_rx_queue (struct efx_channel*) ; 
 int /*<<< orphan*/  efx_free_rx_buffers (struct efx_rx_queue*,struct efx_rx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_loopback_rx_packet (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * efx_rx_buf_va (struct efx_rx_buffer*) ; 
 struct efx_rx_buffer* efx_rx_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_rx_deliver (struct efx_channel*,int /*<<< orphan*/ *,struct efx_rx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_rx_packet_gro (struct efx_channel*,struct efx_rx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_to_cpup (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void __efx_rx_packet(struct efx_channel *channel)
{
	struct efx_nic *efx = channel->efx;
	struct efx_rx_buffer *rx_buf =
		efx_rx_buffer(&channel->rx_queue, channel->rx_pkt_index);
	u8 *eh = efx_rx_buf_va(rx_buf);

	/* Read length from the prefix if necessary.  This already
	 * excludes the length of the prefix itself.
	 */
	if (rx_buf->flags & EFX_RX_PKT_PREFIX_LEN)
		rx_buf->len = le16_to_cpup((__le16 *)
					   (eh + efx->rx_packet_len_offset));

	/* If we're in loopback test, then pass the packet directly to the
	 * loopback layer, and free the rx_buf here
	 */
	if (unlikely(efx->loopback_selftest)) {
		struct efx_rx_queue *rx_queue;

		efx_loopback_rx_packet(efx, eh, rx_buf->len);
		rx_queue = efx_channel_get_rx_queue(channel);
		efx_free_rx_buffers(rx_queue, rx_buf,
				    channel->rx_pkt_n_frags);
		goto out;
	}

	if (unlikely(!(efx->net_dev->features & NETIF_F_RXCSUM)))
		rx_buf->flags &= ~EFX_RX_PKT_CSUMMED;

	if ((rx_buf->flags & EFX_RX_PKT_TCP) && !channel->type->receive_skb)
		efx_rx_packet_gro(channel, rx_buf, channel->rx_pkt_n_frags, eh);
	else
		efx_rx_deliver(channel, eh, rx_buf, channel->rx_pkt_n_frags);
out:
	channel->rx_pkt_n_frags = 0;
}