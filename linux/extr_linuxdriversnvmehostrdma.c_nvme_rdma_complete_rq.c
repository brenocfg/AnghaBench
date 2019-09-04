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
struct request {int dummy; } ;
struct nvme_rdma_request {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 struct nvme_rdma_request* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  nvme_complete_rq (struct request*) ; 
 int /*<<< orphan*/  nvme_rdma_unmap_data (int /*<<< orphan*/ ,struct request*) ; 

__attribute__((used)) static void nvme_rdma_complete_rq(struct request *rq)
{
	struct nvme_rdma_request *req = blk_mq_rq_to_pdu(rq);

	nvme_rdma_unmap_data(req->queue, rq);
	nvme_complete_rq(rq);
}