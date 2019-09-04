#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvmet_req {TYPE_2__* cmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  attributes; } ;
struct TYPE_4__ {TYPE_1__ dsm; } ;

/* Variables and functions */
#define  NVME_DSMGMT_AD 130 
#define  NVME_DSMGMT_IDR 129 
#define  NVME_DSMGMT_IDW 128 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_bdev_execute_discard (struct nvmet_req*) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvmet_bdev_execute_dsm(struct nvmet_req *req)
{
	switch (le32_to_cpu(req->cmd->dsm.attributes)) {
	case NVME_DSMGMT_AD:
		nvmet_bdev_execute_discard(req);
		return;
	case NVME_DSMGMT_IDR:
	case NVME_DSMGMT_IDW:
	default:
		/* Not supported yet */
		nvmet_req_complete(req, 0);
		return;
	}
}