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
struct stmmac_priv {int /*<<< orphan*/  dev; TYPE_1__* plat; } ;
struct TYPE_2__ {scalar_t__ tx_queues_to_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_get_tx_queue (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  netif_tx_start_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmmac_start_all_queues(struct stmmac_priv *priv)
{
	u32 tx_queues_cnt = priv->plat->tx_queues_to_use;
	u32 queue;

	for (queue = 0; queue < tx_queues_cnt; queue++)
		netif_tx_start_queue(netdev_get_tx_queue(priv->dev, queue));
}