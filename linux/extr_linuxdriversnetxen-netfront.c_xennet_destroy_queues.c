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
struct netfront_queue {int /*<<< orphan*/  napi; } ;
struct netfront_info {struct netfront_queue* queues; TYPE_1__* netdev; } ;
struct TYPE_2__ {unsigned int real_num_tx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct netfront_queue*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 scalar_t__ netif_running (TYPE_1__*) ; 

__attribute__((used)) static void xennet_destroy_queues(struct netfront_info *info)
{
	unsigned int i;

	for (i = 0; i < info->netdev->real_num_tx_queues; i++) {
		struct netfront_queue *queue = &info->queues[i];

		if (netif_running(info->netdev))
			napi_disable(&queue->napi);
		netif_napi_del(&queue->napi);
	}

	kfree(info->queues);
	info->queues = NULL;
}