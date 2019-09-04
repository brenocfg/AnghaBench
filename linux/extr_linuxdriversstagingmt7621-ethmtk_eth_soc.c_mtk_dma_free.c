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
struct TYPE_3__ {int /*<<< orphan*/  (* tx_clean ) (struct mtk_eth*) ;} ;
struct mtk_eth {int /*<<< orphan*/  scratch_head; int /*<<< orphan*/ * rx_ring; TYPE_1__ tx_ring; scalar_t__* netdev; TYPE_2__* soc; } ;
struct TYPE_4__ {int mac_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_clean_rx (struct mtk_eth*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_reset_queue (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct mtk_eth*) ; 

__attribute__((used)) static void mtk_dma_free(struct mtk_eth *eth)
{
	int i;

	for (i = 0; i < eth->soc->mac_count; i++)
		if (eth->netdev[i])
			netdev_reset_queue(eth->netdev[i]);
	eth->tx_ring.tx_clean(eth);
	mtk_clean_rx(eth, &eth->rx_ring[0]);
	mtk_clean_rx(eth, &eth->rx_ring[1]);
	kfree(eth->scratch_head);
}