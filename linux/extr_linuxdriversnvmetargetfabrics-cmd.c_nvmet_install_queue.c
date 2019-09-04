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
typedef  int u16 ;
struct nvmf_connect_command {int /*<<< orphan*/  sqsize; int /*<<< orphan*/  qid; } ;
struct nvmet_req {TYPE_2__* sq; int /*<<< orphan*/  cq; TYPE_1__* cmd; } ;
struct nvmet_ctrl {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl; } ;
struct TYPE_3__ {struct nvmf_connect_command connect; } ;

/* Variables and functions */
 int NVME_SC_CONNECT_CTRL_BUSY ; 
 int NVME_SC_CONNECT_INVALID_PARAM ; 
 int NVME_SC_DNR ; 
 struct nvmet_ctrl* cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvmet_ctrl*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_cq_setup (struct nvmet_ctrl*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nvmet_sq_setup (struct nvmet_ctrl*,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static u16 nvmet_install_queue(struct nvmet_ctrl *ctrl, struct nvmet_req *req)
{
	struct nvmf_connect_command *c = &req->cmd->connect;
	u16 qid = le16_to_cpu(c->qid);
	u16 sqsize = le16_to_cpu(c->sqsize);
	struct nvmet_ctrl *old;

	old = cmpxchg(&req->sq->ctrl, NULL, ctrl);
	if (old) {
		pr_warn("queue already connected!\n");
		return NVME_SC_CONNECT_CTRL_BUSY | NVME_SC_DNR;
	}
	if (!sqsize) {
		pr_warn("queue size zero!\n");
		return NVME_SC_CONNECT_INVALID_PARAM | NVME_SC_DNR;
	}

	/* note: convert queue size from 0's-based value to 1's-based value */
	nvmet_cq_setup(ctrl, req->cq, qid, sqsize + 1);
	nvmet_sq_setup(ctrl, req->sq, qid, sqsize + 1);
	return 0;
}