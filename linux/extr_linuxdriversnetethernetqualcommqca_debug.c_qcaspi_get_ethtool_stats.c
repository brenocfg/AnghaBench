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
struct qcaspi_stats {int dummy; } ;
struct qcaspi {struct qcaspi_stats stats; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct qcaspi_stats*,int) ; 
 struct qcaspi* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qcaspi_gstrings_stats ; 

__attribute__((used)) static void
qcaspi_get_ethtool_stats(struct net_device *dev, struct ethtool_stats *estats, u64 *data)
{
	struct qcaspi *qca = netdev_priv(dev);
	struct qcaspi_stats *st = &qca->stats;

	memcpy(data, st, ARRAY_SIZE(qcaspi_gstrings_stats) * sizeof(u64));
}