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
struct vmxnet3_adapter {int num_tx_queues; int num_rx_queues; int /*<<< orphan*/ * rx_queue; int /*<<< orphan*/ * tx_queue; TYPE_1__* shared; } ;
struct TYPE_2__ {int /*<<< orphan*/  ecr; } ;

/* Variables and functions */
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmxnet3_process_events (struct vmxnet3_adapter*) ; 
 scalar_t__ vmxnet3_rq_rx_complete (int /*<<< orphan*/ *,struct vmxnet3_adapter*,int) ; 
 int /*<<< orphan*/  vmxnet3_tq_tx_complete (int /*<<< orphan*/ *,struct vmxnet3_adapter*) ; 

__attribute__((used)) static int
vmxnet3_do_poll(struct vmxnet3_adapter *adapter, int budget)
{
	int rcd_done = 0, i;
	if (unlikely(adapter->shared->ecr))
		vmxnet3_process_events(adapter);
	for (i = 0; i < adapter->num_tx_queues; i++)
		vmxnet3_tq_tx_complete(&adapter->tx_queue[i], adapter);

	for (i = 0; i < adapter->num_rx_queues; i++)
		rcd_done += vmxnet3_rq_rx_complete(&adapter->rx_queue[i],
						   adapter, budget);
	return rcd_done;
}