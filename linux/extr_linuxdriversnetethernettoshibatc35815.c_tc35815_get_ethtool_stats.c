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
struct TYPE_2__ {int /*<<< orphan*/  tx_underrun; int /*<<< orphan*/  rx_ints; int /*<<< orphan*/  tx_ints; int /*<<< orphan*/  max_tx_qlen; } ;
struct tc35815_local {TYPE_1__ lstats; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 struct tc35815_local* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void tc35815_get_ethtool_stats(struct net_device *dev, struct ethtool_stats *stats, u64 *data)
{
	struct tc35815_local *lp = netdev_priv(dev);
	data[0] = lp->lstats.max_tx_qlen;
	data[1] = lp->lstats.tx_ints;
	data[2] = lp->lstats.rx_ints;
	data[3] = lp->lstats.tx_underrun;
}