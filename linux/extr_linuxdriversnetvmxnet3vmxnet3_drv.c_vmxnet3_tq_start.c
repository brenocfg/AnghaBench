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
struct vmxnet3_tx_queue {int stopped; } ;
struct vmxnet3_adapter {int tx_queue; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_start_subqueue (int /*<<< orphan*/ ,struct vmxnet3_tx_queue*) ; 

__attribute__((used)) static void
vmxnet3_tq_start(struct vmxnet3_tx_queue *tq, struct vmxnet3_adapter *adapter)
{
	tq->stopped = false;
	netif_start_subqueue(adapter->netdev, tq - adapter->tx_queue);
}