#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct plat_stmmacenet_data {int clk_csr; int has_gmac; int force_sf_dma_mode; int unicast_filter_entries; int tx_queues_to_use; int rx_queues_to_use; TYPE_3__* rx_queues_cfg; TYPE_2__* tx_queues_cfg; int /*<<< orphan*/  maxmtu; int /*<<< orphan*/  multicast_filter_bins; TYPE_1__* mdio_bus_data; } ;
struct TYPE_6__ {int use_prio; int pkt_route; } ;
struct TYPE_5__ {int use_prio; } ;
struct TYPE_4__ {scalar_t__ phy_mask; int /*<<< orphan*/ * phy_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_TABLE_SIZE ; 
 int /*<<< orphan*/  JUMBO_LEN ; 

__attribute__((used)) static void common_default_data(struct plat_stmmacenet_data *plat)
{
	plat->clk_csr = 2;	/* clk_csr_i = 20-35MHz & MDC = clk_csr_i/16 */
	plat->has_gmac = 1;
	plat->force_sf_dma_mode = 1;

	plat->mdio_bus_data->phy_reset = NULL;
	plat->mdio_bus_data->phy_mask = 0;

	/* Set default value for multicast hash bins */
	plat->multicast_filter_bins = HASH_TABLE_SIZE;

	/* Set default value for unicast filter entries */
	plat->unicast_filter_entries = 1;

	/* Set the maxmtu to a default of JUMBO_LEN */
	plat->maxmtu = JUMBO_LEN;

	/* Set default number of RX and TX queues to use */
	plat->tx_queues_to_use = 1;
	plat->rx_queues_to_use = 1;

	/* Disable Priority config by default */
	plat->tx_queues_cfg[0].use_prio = false;
	plat->rx_queues_cfg[0].use_prio = false;

	/* Disable RX queues routing by default */
	plat->rx_queues_cfg[0].pkt_route = 0x0;
}