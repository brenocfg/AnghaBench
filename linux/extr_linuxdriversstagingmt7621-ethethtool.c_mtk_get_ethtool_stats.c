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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct mtk_mac {struct mtk_hw_stats* hw_stats; } ;
struct mtk_hw_stats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  stats_lock; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_2__ {size_t idx; } ;

/* Variables and functions */
 int MTK_HW_STATS_LEN ; 
 TYPE_1__* mtk_ethtool_hw_stats ; 
 int /*<<< orphan*/  mtk_stats_update_mac (struct mtk_mac*) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_device_present (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void mtk_get_ethtool_stats(struct net_device *dev,
				  struct ethtool_stats *stats, u64 *data)
{
	struct mtk_mac *mac = netdev_priv(dev);
	struct mtk_hw_stats *hwstats = mac->hw_stats;
	unsigned int start;
	int i;

	if (netif_running(dev) && netif_device_present(dev)) {
		if (spin_trylock(&hwstats->stats_lock)) {
			mtk_stats_update_mac(mac);
			spin_unlock(&hwstats->stats_lock);
		}
	}

	do {
		start = u64_stats_fetch_begin_irq(&hwstats->syncp);
		for (i = 0; i < MTK_HW_STATS_LEN; i++)
			data[i] = ((u64 *)hwstats)[mtk_ethtool_hw_stats[i].idx];

	} while (u64_stats_fetch_retry_irq(&hwstats->syncp, start));
}