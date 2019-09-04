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
struct net_device {int dummy; } ;
struct mtk_soc_data {scalar_t__* reg_table; } ;
struct mtk_mac {TYPE_2__* hw; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  n_stats; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; } ;
struct TYPE_6__ {TYPE_1__* driver; } ;
struct TYPE_5__ {TYPE_3__* dev; struct mtk_soc_data* soc; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_HW_STATS_LEN ; 
 size_t MTK_REG_MTK_COUNTER_BASE ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mtk_get_drvinfo(struct net_device *dev,
			    struct ethtool_drvinfo *info)
{
	struct mtk_mac *mac = netdev_priv(dev);
	struct mtk_soc_data *soc = mac->hw->soc;

	strlcpy(info->driver, mac->hw->dev->driver->name, sizeof(info->driver));
	strlcpy(info->bus_info, dev_name(mac->hw->dev), sizeof(info->bus_info));

	if (soc->reg_table[MTK_REG_MTK_COUNTER_BASE])
		info->n_stats = MTK_HW_STATS_LEN;
}