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
struct nvme_rdma_queue {int queue_size; int /*<<< orphan*/ * rsp_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_rdma_destroy_queue_ib (struct nvme_rdma_queue*) ; 
 int nvme_rdma_post_recv (struct nvme_rdma_queue*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvme_rdma_conn_established(struct nvme_rdma_queue *queue)
{
	int ret, i;

	for (i = 0; i < queue->queue_size; i++) {
		ret = nvme_rdma_post_recv(queue, &queue->rsp_ring[i]);
		if (ret)
			goto out_destroy_queue_ib;
	}

	return 0;

out_destroy_queue_ib:
	nvme_rdma_destroy_queue_ib(queue);
	return ret;
}