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
typedef  scalar_t__ u32 ;
struct stmmac_priv {int /*<<< orphan*/  ioaddr; TYPE_1__* plat; } ;
struct TYPE_2__ {scalar_t__ rx_queues_to_use; scalar_t__ tx_queues_to_use; } ;

/* Variables and functions */
 scalar_t__ DMA_RX_SIZE ; 
 scalar_t__ DMA_TX_SIZE ; 
 int /*<<< orphan*/  stmmac_set_rx_ring_len (struct stmmac_priv*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stmmac_set_tx_ring_len (struct stmmac_priv*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void stmmac_set_rings_length(struct stmmac_priv *priv)
{
	u32 rx_channels_count = priv->plat->rx_queues_to_use;
	u32 tx_channels_count = priv->plat->tx_queues_to_use;
	u32 chan;

	/* set TX ring length */
	for (chan = 0; chan < tx_channels_count; chan++)
		stmmac_set_tx_ring_len(priv, priv->ioaddr,
				(DMA_TX_SIZE - 1), chan);

	/* set RX ring length */
	for (chan = 0; chan < rx_channels_count; chan++)
		stmmac_set_rx_ring_len(priv, priv->ioaddr,
				(DMA_RX_SIZE - 1), chan);
}