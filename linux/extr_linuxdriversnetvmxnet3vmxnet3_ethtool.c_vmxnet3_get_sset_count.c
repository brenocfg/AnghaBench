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
struct vmxnet3_adapter {int num_tx_queues; int num_rx_queues; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 128 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vmxnet3_global_stats ; 
 int /*<<< orphan*/  vmxnet3_rq_dev_stats ; 
 int /*<<< orphan*/  vmxnet3_rq_driver_stats ; 
 int /*<<< orphan*/  vmxnet3_tq_dev_stats ; 
 int /*<<< orphan*/  vmxnet3_tq_driver_stats ; 

__attribute__((used)) static int
vmxnet3_get_sset_count(struct net_device *netdev, int sset)
{
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);
	switch (sset) {
	case ETH_SS_STATS:
		return (ARRAY_SIZE(vmxnet3_tq_dev_stats) +
			ARRAY_SIZE(vmxnet3_tq_driver_stats)) *
		       adapter->num_tx_queues +
		       (ARRAY_SIZE(vmxnet3_rq_dev_stats) +
			ARRAY_SIZE(vmxnet3_rq_driver_stats)) *
		       adapter->num_rx_queues +
			ARRAY_SIZE(vmxnet3_global_stats);
	default:
		return -EOPNOTSUPP;
	}
}