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
struct stmmac_priv {TYPE_1__* plat; } ;
struct TYPE_2__ {scalar_t__ rx_queues_to_use; scalar_t__ tx_queues_to_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  stmmac_stop_rx_dma (struct stmmac_priv*,scalar_t__) ; 
 int /*<<< orphan*/  stmmac_stop_tx_dma (struct stmmac_priv*,scalar_t__) ; 

__attribute__((used)) static void stmmac_stop_all_dma(struct stmmac_priv *priv)
{
	u32 rx_channels_count = priv->plat->rx_queues_to_use;
	u32 tx_channels_count = priv->plat->tx_queues_to_use;
	u32 chan = 0;

	for (chan = 0; chan < rx_channels_count; chan++)
		stmmac_stop_rx_dma(priv, chan);

	for (chan = 0; chan < tx_channels_count; chan++)
		stmmac_stop_tx_dma(priv, chan);
}