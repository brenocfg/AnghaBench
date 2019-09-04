#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int desc_size; int /*<<< orphan*/ * base; int /*<<< orphan*/  basePA; } ;
struct vmxnet3_rx_queue {TYPE_3__ data_ring; TYPE_2__* rx_ring; } ;
struct vmxnet3_adapter {int num_rx_queues; TYPE_1__* pdev; struct vmxnet3_rx_queue* rx_queue; } ;
struct TYPE_5__ {int size; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmxnet3_rq_destroy_all_rxdataring(struct vmxnet3_adapter *adapter)
{
	int i;

	for (i = 0; i < adapter->num_rx_queues; i++) {
		struct vmxnet3_rx_queue *rq = &adapter->rx_queue[i];

		if (rq->data_ring.base) {
			dma_free_coherent(&adapter->pdev->dev,
					  (rq->rx_ring[0].size *
					  rq->data_ring.desc_size),
					  rq->data_ring.base,
					  rq->data_ring.basePA);
			rq->data_ring.base = NULL;
			rq->data_ring.desc_size = 0;
		}
	}
}