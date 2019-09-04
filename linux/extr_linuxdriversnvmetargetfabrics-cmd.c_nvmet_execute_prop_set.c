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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct nvmet_req {TYPE_1__* sq; TYPE_3__* cmd; } ;
struct TYPE_5__ {int attrib; int /*<<< orphan*/  offset; int /*<<< orphan*/  value; } ;
struct TYPE_6__ {TYPE_2__ prop_set; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
#define  NVME_REG_CC 128 
 int NVME_SC_DNR ; 
 int NVME_SC_INVALID_FIELD ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int) ; 
 int /*<<< orphan*/  nvmet_update_cc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvmet_execute_prop_set(struct nvmet_req *req)
{
	u16 status = 0;

	if (!(req->cmd->prop_set.attrib & 1)) {
		u64 val = le64_to_cpu(req->cmd->prop_set.value);

		switch (le32_to_cpu(req->cmd->prop_set.offset)) {
		case NVME_REG_CC:
			nvmet_update_cc(req->sq->ctrl, val);
			break;
		default:
			status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
			break;
		}
	} else {
		status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
	}

	nvmet_req_complete(req, status);
}