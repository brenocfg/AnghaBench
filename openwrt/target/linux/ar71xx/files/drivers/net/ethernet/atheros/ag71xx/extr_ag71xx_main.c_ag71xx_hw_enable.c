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
struct TYPE_4__ {int /*<<< orphan*/  descs_dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  descs_dma; } ;
struct ag71xx {int /*<<< orphan*/  dev; TYPE_2__ rx_ring; TYPE_1__ tx_ring; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_RX_DESC ; 
 int /*<<< orphan*/  AG71XX_REG_TX_DESC ; 
 int ag71xx_rings_init (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_start_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ag71xx_hw_enable(struct ag71xx *ag)
{
	int ret;

	ret = ag71xx_rings_init(ag);
	if (ret)
		return ret;

	napi_enable(&ag->napi);
	ag71xx_wr(ag, AG71XX_REG_TX_DESC, ag->tx_ring.descs_dma);
	ag71xx_wr(ag, AG71XX_REG_RX_DESC, ag->rx_ring.descs_dma);
	netif_start_queue(ag->dev);

	return 0;
}