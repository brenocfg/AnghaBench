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
typedef  int u64 ;
struct mtk_mac {TYPE_2__* hw; struct mtk_hw_stats* hw_stats; } ;
struct mtk_hw_stats {int rx_bytes; int rx_packets; int rx_overflow; int rx_fcs_errors; int rx_short_errors; int rx_long_errors; int rx_checksum_errors; int rx_flow_control_packets; int tx_skip; int tx_collisions; int tx_bytes; int tx_packets; int /*<<< orphan*/  syncp; scalar_t__ reg_offset; } ;
struct TYPE_4__ {TYPE_1__* soc; } ;
struct TYPE_3__ {scalar_t__ new_stats; } ;

/* Variables and functions */
 size_t MTK_REG_MTK_COUNTER_BASE ; 
 int mtk_r32 (TYPE_2__*,unsigned int) ; 
 unsigned int* mtk_reg_table ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

void mtk_stats_update_mac(struct mtk_mac *mac)
{
	struct mtk_hw_stats *hw_stats = mac->hw_stats;
	unsigned int base = mtk_reg_table[MTK_REG_MTK_COUNTER_BASE];
	u64 stats;

	base += hw_stats->reg_offset;

	u64_stats_update_begin(&hw_stats->syncp);

	if (mac->hw->soc->new_stats) {
		hw_stats->rx_bytes += mtk_r32(mac->hw, base);
		stats =  mtk_r32(mac->hw, base + 0x04);
		if (stats)
			hw_stats->rx_bytes += (stats << 32);
		hw_stats->rx_packets += mtk_r32(mac->hw, base + 0x08);
		hw_stats->rx_overflow += mtk_r32(mac->hw, base + 0x10);
		hw_stats->rx_fcs_errors += mtk_r32(mac->hw, base + 0x14);
		hw_stats->rx_short_errors += mtk_r32(mac->hw, base + 0x18);
		hw_stats->rx_long_errors += mtk_r32(mac->hw, base + 0x1c);
		hw_stats->rx_checksum_errors += mtk_r32(mac->hw, base + 0x20);
		hw_stats->rx_flow_control_packets +=
						mtk_r32(mac->hw, base + 0x24);
		hw_stats->tx_skip += mtk_r32(mac->hw, base + 0x28);
		hw_stats->tx_collisions += mtk_r32(mac->hw, base + 0x2c);
		hw_stats->tx_bytes += mtk_r32(mac->hw, base + 0x30);
		stats =  mtk_r32(mac->hw, base + 0x34);
		if (stats)
			hw_stats->tx_bytes += (stats << 32);
		hw_stats->tx_packets += mtk_r32(mac->hw, base + 0x38);
	} else {
		hw_stats->tx_bytes += mtk_r32(mac->hw, base);
		hw_stats->tx_packets += mtk_r32(mac->hw, base + 0x04);
		hw_stats->tx_skip += mtk_r32(mac->hw, base + 0x08);
		hw_stats->tx_collisions += mtk_r32(mac->hw, base + 0x0c);
		hw_stats->rx_bytes += mtk_r32(mac->hw, base + 0x20);
		hw_stats->rx_packets += mtk_r32(mac->hw, base + 0x24);
		hw_stats->rx_overflow += mtk_r32(mac->hw, base + 0x28);
		hw_stats->rx_fcs_errors += mtk_r32(mac->hw, base + 0x2c);
		hw_stats->rx_short_errors += mtk_r32(mac->hw, base + 0x30);
		hw_stats->rx_long_errors += mtk_r32(mac->hw, base + 0x34);
		hw_stats->rx_checksum_errors += mtk_r32(mac->hw, base + 0x38);
		hw_stats->rx_flow_control_packets +=
						mtk_r32(mac->hw, base + 0x3c);
	}

	u64_stats_update_end(&hw_stats->syncp);
}