#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct rtl8169_private {struct rtl8169_counters* counters; } ;
struct rtl8169_counters {int /*<<< orphan*/  tx_underun; int /*<<< orphan*/  tx_aborted; int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  rx_broadcast; int /*<<< orphan*/  rx_unicast; int /*<<< orphan*/  tx_multi_collision; int /*<<< orphan*/  tx_one_collision; int /*<<< orphan*/  align_errors; int /*<<< orphan*/  rx_missed; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 scalar_t__ pm_runtime_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  rtl8169_update_counters (struct rtl8169_private*) ; 
 struct device* tp_to_dev (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl8169_get_ethtool_stats(struct net_device *dev,
				      struct ethtool_stats *stats, u64 *data)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	struct device *d = tp_to_dev(tp);
	struct rtl8169_counters *counters = tp->counters;

	ASSERT_RTNL();

	pm_runtime_get_noresume(d);

	if (pm_runtime_active(d))
		rtl8169_update_counters(tp);

	pm_runtime_put_noidle(d);

	data[0] = le64_to_cpu(counters->tx_packets);
	data[1] = le64_to_cpu(counters->rx_packets);
	data[2] = le64_to_cpu(counters->tx_errors);
	data[3] = le32_to_cpu(counters->rx_errors);
	data[4] = le16_to_cpu(counters->rx_missed);
	data[5] = le16_to_cpu(counters->align_errors);
	data[6] = le32_to_cpu(counters->tx_one_collision);
	data[7] = le32_to_cpu(counters->tx_multi_collision);
	data[8] = le64_to_cpu(counters->rx_unicast);
	data[9] = le64_to_cpu(counters->rx_broadcast);
	data[10] = le32_to_cpu(counters->rx_multicast);
	data[11] = le16_to_cpu(counters->tx_aborted);
	data[12] = le16_to_cpu(counters->tx_underun);
}