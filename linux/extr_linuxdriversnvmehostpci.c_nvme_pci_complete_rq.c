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
struct request {int dummy; } ;
struct nvme_iod {TYPE_1__* nvmeq; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct nvme_iod* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  nvme_complete_rq (struct request*) ; 
 int /*<<< orphan*/  nvme_unmap_data (int /*<<< orphan*/ ,struct request*) ; 

__attribute__((used)) static void nvme_pci_complete_rq(struct request *req)
{
	struct nvme_iod *iod = blk_mq_rq_to_pdu(req);

	nvme_unmap_data(iod->nvmeq->dev, req);
	nvme_complete_rq(req);
}