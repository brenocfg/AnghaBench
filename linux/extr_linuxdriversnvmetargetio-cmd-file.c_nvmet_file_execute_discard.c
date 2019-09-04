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
typedef  int u16 ;
struct nvmet_req {TYPE_3__* ns; TYPE_2__* cmd; } ;
struct nvme_dsm_range {int /*<<< orphan*/  nlb; int /*<<< orphan*/  slba; } ;
typedef  int /*<<< orphan*/  range ;
typedef  int loff_t ;
struct TYPE_6__ {int blksize_shift; int size; int /*<<< orphan*/  file; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr; } ;
struct TYPE_5__ {TYPE_1__ dsm; } ;

/* Variables and functions */
 int FALLOC_FL_KEEP_SIZE ; 
 int FALLOC_FL_PUNCH_HOLE ; 
 int NVME_SC_DNR ; 
 int NVME_SC_INTERNAL ; 
 int NVME_SC_LBA_RANGE ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int nvmet_copy_from_sgl (struct nvmet_req*,int,struct nvme_dsm_range*,int) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int) ; 
 scalar_t__ vfs_fallocate (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void nvmet_file_execute_discard(struct nvmet_req *req)
{
	int mode = FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE;
	struct nvme_dsm_range range;
	loff_t offset, len;
	u16 ret;
	int i;

	for (i = 0; i <= le32_to_cpu(req->cmd->dsm.nr); i++) {
		ret = nvmet_copy_from_sgl(req, i * sizeof(range), &range,
					sizeof(range));
		if (ret)
			break;

		offset = le64_to_cpu(range.slba) << req->ns->blksize_shift;
		len = le32_to_cpu(range.nlb) << req->ns->blksize_shift;
		if (offset + len > req->ns->size) {
			ret = NVME_SC_LBA_RANGE | NVME_SC_DNR;
			break;
		}

		if (vfs_fallocate(req->ns->file, mode, offset, len)) {
			ret = NVME_SC_INTERNAL | NVME_SC_DNR;
			break;
		}
	}

	nvmet_req_complete(req, ret);
}