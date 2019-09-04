#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct vmxnet3_adapter {int num_tx_queues; int num_rx_queues; } ;
struct net_device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
 scalar_t__ ETH_SS_STATS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 
 TYPE_1__* vmxnet3_global_stats ; 
 TYPE_1__* vmxnet3_rq_dev_stats ; 
 TYPE_1__* vmxnet3_rq_driver_stats ; 
 TYPE_1__* vmxnet3_tq_dev_stats ; 
 TYPE_1__* vmxnet3_tq_driver_stats ; 

__attribute__((used)) static void
vmxnet3_get_strings(struct net_device *netdev, u32 stringset, u8 *buf)
{
	 struct vmxnet3_adapter *adapter = netdev_priv(netdev);
	if (stringset == ETH_SS_STATS) {
		int i, j;
		for (j = 0; j < adapter->num_tx_queues; j++) {
			for (i = 0; i < ARRAY_SIZE(vmxnet3_tq_dev_stats); i++) {
				memcpy(buf, vmxnet3_tq_dev_stats[i].desc,
				       ETH_GSTRING_LEN);
				buf += ETH_GSTRING_LEN;
			}
			for (i = 0; i < ARRAY_SIZE(vmxnet3_tq_driver_stats);
			     i++) {
				memcpy(buf, vmxnet3_tq_driver_stats[i].desc,
				       ETH_GSTRING_LEN);
				buf += ETH_GSTRING_LEN;
			}
		}

		for (j = 0; j < adapter->num_rx_queues; j++) {
			for (i = 0; i < ARRAY_SIZE(vmxnet3_rq_dev_stats); i++) {
				memcpy(buf, vmxnet3_rq_dev_stats[i].desc,
				       ETH_GSTRING_LEN);
				buf += ETH_GSTRING_LEN;
			}
			for (i = 0; i < ARRAY_SIZE(vmxnet3_rq_driver_stats);
			     i++) {
				memcpy(buf, vmxnet3_rq_driver_stats[i].desc,
				       ETH_GSTRING_LEN);
				buf += ETH_GSTRING_LEN;
			}
		}

		for (i = 0; i < ARRAY_SIZE(vmxnet3_global_stats); i++) {
			memcpy(buf, vmxnet3_global_stats[i].desc,
				ETH_GSTRING_LEN);
			buf += ETH_GSTRING_LEN;
		}
	}
}