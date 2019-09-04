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
 int /*<<< orphan*/  stmmac_clear_rx_descriptors (struct stmmac_priv*,scalar_t__) ; 
 int /*<<< orphan*/  stmmac_clear_tx_descriptors (struct stmmac_priv*,scalar_t__) ; 

__attribute__((used)) static void stmmac_clear_descriptors(struct stmmac_priv *priv)
{
	u32 rx_queue_cnt = priv->plat->rx_queues_to_use;
	u32 tx_queue_cnt = priv->plat->tx_queues_to_use;
	u32 queue;

	/* Clear the RX descriptors */
	for (queue = 0; queue < rx_queue_cnt; queue++)
		stmmac_clear_rx_descriptors(priv, queue);

	/* Clear the TX descriptors */
	for (queue = 0; queue < tx_queue_cnt; queue++)
		stmmac_clear_tx_descriptors(priv, queue);
}