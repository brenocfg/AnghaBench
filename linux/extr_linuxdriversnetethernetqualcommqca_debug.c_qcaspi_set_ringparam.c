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
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
struct qcaspi {TYPE_1__ txr; } ;
struct net_device_ops {int /*<<< orphan*/  (* ndo_open ) (struct net_device*) ;int /*<<< orphan*/  (* ndo_stop ) (struct net_device*) ;} ;
struct net_device {struct net_device_ops* netdev_ops; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; scalar_t__ rx_pending; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TX_RING_MAX_LEN ; 
 int /*<<< orphan*/  TX_RING_MIN_LEN ; 
 int /*<<< orphan*/  max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qcaspi* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*) ; 
 int /*<<< orphan*/  u16 ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static int
qcaspi_set_ringparam(struct net_device *dev, struct ethtool_ringparam *ring)
{
	const struct net_device_ops *ops = dev->netdev_ops;
	struct qcaspi *qca = netdev_priv(dev);

	if ((ring->rx_pending) ||
	    (ring->rx_mini_pending) ||
	    (ring->rx_jumbo_pending))
		return -EINVAL;

	if (netif_running(dev))
		ops->ndo_stop(dev);

	qca->txr.count = max_t(u32, ring->tx_pending, TX_RING_MIN_LEN);
	qca->txr.count = min_t(u16, qca->txr.count, TX_RING_MAX_LEN);

	if (netif_running(dev))
		ops->ndo_open(dev);

	return 0;
}