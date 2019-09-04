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
typedef  size_t u32 ;
struct stmmac_priv {int /*<<< orphan*/  hw; TYPE_2__* plat; } ;
struct TYPE_4__ {size_t rx_queues_to_use; TYPE_1__* rx_queues_cfg; } ;
struct TYPE_3__ {size_t prio; int /*<<< orphan*/  use_prio; } ;

/* Variables and functions */
 int /*<<< orphan*/  stmmac_rx_queue_prio (struct stmmac_priv*,int /*<<< orphan*/ ,size_t,size_t) ; 

__attribute__((used)) static void stmmac_mac_config_rx_queues_prio(struct stmmac_priv *priv)
{
	u32 rx_queues_count = priv->plat->rx_queues_to_use;
	u32 queue;
	u32 prio;

	for (queue = 0; queue < rx_queues_count; queue++) {
		if (!priv->plat->rx_queues_cfg[queue].use_prio)
			continue;

		prio = priv->plat->rx_queues_cfg[queue].prio;
		stmmac_rx_queue_prio(priv, priv->hw, prio, queue);
	}
}