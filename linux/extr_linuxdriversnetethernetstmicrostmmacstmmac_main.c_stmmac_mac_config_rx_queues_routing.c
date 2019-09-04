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
typedef  int u8 ;
typedef  size_t u32 ;
struct stmmac_priv {int /*<<< orphan*/  hw; TYPE_1__* plat; } ;
struct TYPE_4__ {int pkt_route; } ;
struct TYPE_3__ {size_t rx_queues_to_use; TYPE_2__* rx_queues_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  stmmac_rx_queue_routing (struct stmmac_priv*,int /*<<< orphan*/ ,int,size_t) ; 

__attribute__((used)) static void stmmac_mac_config_rx_queues_routing(struct stmmac_priv *priv)
{
	u32 rx_queues_count = priv->plat->rx_queues_to_use;
	u32 queue;
	u8 packet;

	for (queue = 0; queue < rx_queues_count; queue++) {
		/* no specific packet type routing specified for the queue */
		if (priv->plat->rx_queues_cfg[queue].pkt_route == 0x0)
			continue;

		packet = priv->plat->rx_queues_cfg[queue].pkt_route;
		stmmac_rx_queue_routing(priv, priv->hw, packet, queue);
	}
}