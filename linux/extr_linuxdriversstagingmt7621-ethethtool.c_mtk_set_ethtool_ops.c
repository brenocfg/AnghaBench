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
struct net_device {TYPE_2__* ethtool_ops; } ;
struct mtk_soc_data {scalar_t__* reg_table; } ;
struct mtk_mac {TYPE_1__* hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  get_ethtool_stats; int /*<<< orphan*/  get_sset_count; int /*<<< orphan*/  get_strings; } ;
struct TYPE_3__ {struct mtk_soc_data* soc; } ;

/* Variables and functions */
 size_t MTK_REG_MTK_COUNTER_BASE ; 
 TYPE_2__ mtk_ethtool_ops ; 
 int /*<<< orphan*/  mtk_get_ethtool_stats ; 
 int /*<<< orphan*/  mtk_get_sset_count ; 
 int /*<<< orphan*/  mtk_get_strings ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 

void mtk_set_ethtool_ops(struct net_device *netdev)
{
	struct mtk_mac *mac = netdev_priv(netdev);
	struct mtk_soc_data *soc = mac->hw->soc;

	if (soc->reg_table[MTK_REG_MTK_COUNTER_BASE]) {
		mtk_ethtool_ops.get_strings = mtk_get_strings;
		mtk_ethtool_ops.get_sset_count = mtk_get_sset_count;
		mtk_ethtool_ops.get_ethtool_stats = mtk_get_ethtool_stats;
	}

	netdev->ethtool_ops = &mtk_ethtool_ops;
}