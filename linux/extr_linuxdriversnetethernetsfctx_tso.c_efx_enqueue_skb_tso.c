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
struct tso_state {scalar_t__ in_len; scalar_t__ packet_space; scalar_t__ header_unmap_len; int /*<<< orphan*/  header_dma_addr; scalar_t__ unmap_len; int /*<<< orphan*/  unmap_addr; int /*<<< orphan*/  protocol; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct efx_tx_queue {int tso_version; scalar_t__ write_count; scalar_t__ insert_count; struct efx_nic* efx; } ;
struct efx_nic {TYPE_1__* pci_dev; int /*<<< orphan*/  net_dev; } ;
struct TYPE_4__ {int nr_frags; scalar_t__ frags; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  EFX_WARN_ON_ONCE_PARANOID (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_tso_check_protocol (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch_ptr (struct efx_tx_queue*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  tso_fill_packet_with_fragment (struct efx_tx_queue*,struct sk_buff*,struct tso_state*) ; 
 int tso_get_fragment (struct tso_state*,struct efx_nic*,scalar_t__) ; 
 int tso_start (struct tso_state*,struct efx_nic*,struct efx_tx_queue*,struct sk_buff*) ; 
 int tso_start_new_packet (struct efx_tx_queue*,struct sk_buff*,struct tso_state*) ; 
 int /*<<< orphan*/  tx_err ; 

int efx_enqueue_skb_tso(struct efx_tx_queue *tx_queue,
			struct sk_buff *skb,
			bool *data_mapped)
{
	struct efx_nic *efx = tx_queue->efx;
	int frag_i, rc;
	struct tso_state state;

	if (tx_queue->tso_version != 1)
		return -EINVAL;

	prefetch(skb->data);

	/* Find the packet protocol and sanity-check it */
	state.protocol = efx_tso_check_protocol(skb);

	EFX_WARN_ON_ONCE_PARANOID(tx_queue->write_count != tx_queue->insert_count);

	rc = tso_start(&state, efx, tx_queue, skb);
	if (rc)
		goto fail;

	if (likely(state.in_len == 0)) {
		/* Grab the first payload fragment. */
		EFX_WARN_ON_ONCE_PARANOID(skb_shinfo(skb)->nr_frags < 1);
		frag_i = 0;
		rc = tso_get_fragment(&state, efx,
				      skb_shinfo(skb)->frags + frag_i);
		if (rc)
			goto fail;
	} else {
		/* Payload starts in the header area. */
		frag_i = -1;
	}

	rc = tso_start_new_packet(tx_queue, skb, &state);
	if (rc)
		goto fail;

	prefetch_ptr(tx_queue);

	while (1) {
		tso_fill_packet_with_fragment(tx_queue, skb, &state);

		/* Move onto the next fragment? */
		if (state.in_len == 0) {
			if (++frag_i >= skb_shinfo(skb)->nr_frags)
				/* End of payload reached. */
				break;
			rc = tso_get_fragment(&state, efx,
					      skb_shinfo(skb)->frags + frag_i);
			if (rc)
				goto fail;
		}

		/* Start at new packet? */
		if (state.packet_space == 0) {
			rc = tso_start_new_packet(tx_queue, skb, &state);
			if (rc)
				goto fail;
		}
	}

	*data_mapped = true;

	return 0;

fail:
	if (rc == -ENOMEM)
		netif_err(efx, tx_err, efx->net_dev,
			  "Out of memory for TSO headers, or DMA mapping error\n");
	else
		netif_err(efx, tx_err, efx->net_dev, "TSO failed, rc = %d\n", rc);

	/* Free the DMA mapping we were in the process of writing out */
	if (state.unmap_len) {
		dma_unmap_page(&efx->pci_dev->dev, state.unmap_addr,
			       state.unmap_len, DMA_TO_DEVICE);
	}

	/* Free the header DMA mapping */
	if (state.header_unmap_len)
		dma_unmap_single(&efx->pci_dev->dev, state.header_dma_addr,
				 state.header_unmap_len, DMA_TO_DEVICE);

	return rc;
}