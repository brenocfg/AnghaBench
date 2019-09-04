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
struct tso_state {scalar_t__ in_len; scalar_t__ packet_space; scalar_t__ out_len; int dma_addr; scalar_t__ unmap_len; } ;
struct sk_buff {int dummy; } ;
struct efx_tx_queue {int dummy; } ;
struct efx_tx_buffer {scalar_t__ len; scalar_t__ unmap_len; scalar_t__ dma_offset; int /*<<< orphan*/  flags; struct sk_buff const* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_TX_BUF_CONT ; 
 int /*<<< orphan*/  EFX_TX_BUF_SKB ; 
 int /*<<< orphan*/  EFX_WARN_ON_ONCE_PARANOID (int) ; 
 int /*<<< orphan*/  efx_tx_queue_insert (struct efx_tx_queue*,int,int,struct efx_tx_buffer**) ; 
 int min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void tso_fill_packet_with_fragment(struct efx_tx_queue *tx_queue,
					  const struct sk_buff *skb,
					  struct tso_state *st)
{
	struct efx_tx_buffer *buffer;
	int n;

	if (st->in_len == 0)
		return;
	if (st->packet_space == 0)
		return;

	EFX_WARN_ON_ONCE_PARANOID(st->in_len <= 0);
	EFX_WARN_ON_ONCE_PARANOID(st->packet_space <= 0);

	n = min(st->in_len, st->packet_space);

	st->packet_space -= n;
	st->out_len -= n;
	st->in_len -= n;

	efx_tx_queue_insert(tx_queue, st->dma_addr, n, &buffer);

	if (st->out_len == 0) {
		/* Transfer ownership of the skb */
		buffer->skb = skb;
		buffer->flags = EFX_TX_BUF_SKB;
	} else if (st->packet_space != 0) {
		buffer->flags = EFX_TX_BUF_CONT;
	}

	if (st->in_len == 0) {
		/* Transfer ownership of the DMA mapping */
		buffer->unmap_len = st->unmap_len;
		buffer->dma_offset = buffer->unmap_len - buffer->len;
		st->unmap_len = 0;
	}

	st->dma_addr += n;
}