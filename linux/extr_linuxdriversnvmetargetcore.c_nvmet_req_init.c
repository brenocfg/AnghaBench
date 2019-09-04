#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct nvmet_sq {scalar_t__ qid; int /*<<< orphan*/  ref; TYPE_5__* ctrl; } ;
struct nvmet_req {struct nvmet_sq* sq; TYPE_3__* cmd; int /*<<< orphan*/ * ns; TYPE_1__* rsp; scalar_t__ transfer_len; scalar_t__ sg_cnt; int /*<<< orphan*/ * sg; struct nvmet_fabrics_ops const* ops; struct nvmet_cq* cq; } ;
struct nvmet_fabrics_ops {int dummy; } ;
struct nvmet_cq {int dummy; } ;
struct TYPE_10__ {TYPE_4__* subsys; } ;
struct TYPE_9__ {scalar_t__ type; } ;
struct TYPE_7__ {int flags; scalar_t__ opcode; } ;
struct TYPE_8__ {TYPE_2__ common; } ;
struct TYPE_6__ {scalar_t__ status; } ;

/* Variables and functions */
 int NVME_CMD_FUSE_FIRST ; 
 int NVME_CMD_FUSE_SECOND ; 
 int NVME_CMD_SGL_ALL ; 
 int NVME_CMD_SGL_METABUF ; 
 scalar_t__ NVME_NQN_DISC ; 
 int NVME_SC_DNR ; 
 int NVME_SC_INVALID_FIELD ; 
 int /*<<< orphan*/  __nvmet_req_complete (struct nvmet_req*,int) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ nvme_fabrics_command ; 
 int nvmet_parse_admin_cmd (struct nvmet_req*) ; 
 int nvmet_parse_connect_cmd (struct nvmet_req*) ; 
 int nvmet_parse_discovery_cmd (struct nvmet_req*) ; 
 int nvmet_parse_fabrics_cmd (struct nvmet_req*) ; 
 int nvmet_parse_io_cmd (struct nvmet_req*) ; 
 int /*<<< orphan*/  percpu_ref_tryget_live (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

bool nvmet_req_init(struct nvmet_req *req, struct nvmet_cq *cq,
		struct nvmet_sq *sq, const struct nvmet_fabrics_ops *ops)
{
	u8 flags = req->cmd->common.flags;
	u16 status;

	req->cq = cq;
	req->sq = sq;
	req->ops = ops;
	req->sg = NULL;
	req->sg_cnt = 0;
	req->transfer_len = 0;
	req->rsp->status = 0;
	req->ns = NULL;

	/* no support for fused commands yet */
	if (unlikely(flags & (NVME_CMD_FUSE_FIRST | NVME_CMD_FUSE_SECOND))) {
		status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		goto fail;
	}

	/*
	 * For fabrics, PSDT field shall describe metadata pointer (MPTR) that
	 * contains an address of a single contiguous physical buffer that is
	 * byte aligned.
	 */
	if (unlikely((flags & NVME_CMD_SGL_ALL) != NVME_CMD_SGL_METABUF)) {
		status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		goto fail;
	}

	if (unlikely(!req->sq->ctrl))
		/* will return an error for any Non-connect command: */
		status = nvmet_parse_connect_cmd(req);
	else if (likely(req->sq->qid != 0))
		status = nvmet_parse_io_cmd(req);
	else if (req->cmd->common.opcode == nvme_fabrics_command)
		status = nvmet_parse_fabrics_cmd(req);
	else if (req->sq->ctrl->subsys->type == NVME_NQN_DISC)
		status = nvmet_parse_discovery_cmd(req);
	else
		status = nvmet_parse_admin_cmd(req);

	if (status)
		goto fail;

	if (unlikely(!percpu_ref_tryget_live(&sq->ref))) {
		status = NVME_SC_INVALID_FIELD | NVME_SC_DNR;
		goto fail;
	}

	return true;

fail:
	__nvmet_req_complete(req, status);
	return false;
}