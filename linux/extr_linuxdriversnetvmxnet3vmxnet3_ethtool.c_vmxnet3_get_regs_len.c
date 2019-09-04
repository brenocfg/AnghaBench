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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int num_intrs; } ;
struct vmxnet3_adapter {int num_tx_queues; int num_rx_queues; TYPE_1__ intr; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
vmxnet3_get_regs_len(struct net_device *netdev)
{
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);

	return ((9 /* BAR1 registers */ +
		(1 + adapter->intr.num_intrs) +
		(1 + adapter->num_tx_queues * 17 /* Tx queue registers */) +
		(1 + adapter->num_rx_queues * 23 /* Rx queue registers */)) *
		sizeof(u32));
}