#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct nvmf_connect_data {int /*<<< orphan*/  hostid; int /*<<< orphan*/  hostnqn; int /*<<< orphan*/  subsysnqn; int /*<<< orphan*/  cntlid; } ;
struct nvmf_connect_command {scalar_t__ recfmt; int /*<<< orphan*/  kato; } ;
struct nvmet_req {TYPE_4__* rsp; TYPE_1__* cmd; } ;
struct nvmet_ctrl {int cntlid; int /*<<< orphan*/  hostnqn; TYPE_2__* subsys; int /*<<< orphan*/  hostid; } ;
struct TYPE_7__ {int /*<<< orphan*/  u16; scalar_t__ u32; } ;
struct TYPE_8__ {TYPE_3__ result; } ;
struct TYPE_6__ {int /*<<< orphan*/  subsysnqn; } ;
struct TYPE_5__ {struct nvmf_connect_command connect; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IPO_IATTR_CONNECT_DATA (int /*<<< orphan*/ ) ; 
 int NVME_SC_CONNECT_FORMAT ; 
 int NVME_SC_CONNECT_INVALID_PARAM ; 
 int NVME_SC_DNR ; 
 int NVME_SC_INTERNAL ; 
 int /*<<< orphan*/  cntlid ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct nvmf_connect_data*) ; 
 struct nvmf_connect_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int nvmet_alloc_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvmet_req*,int /*<<< orphan*/ ,struct nvmet_ctrl**) ; 
 int nvmet_copy_from_sgl (struct nvmet_req*,int /*<<< orphan*/ ,struct nvmf_connect_data*,int) ; 
 int /*<<< orphan*/  nvmet_ctrl_put (struct nvmet_ctrl*) ; 
 int nvmet_install_queue (struct nvmet_ctrl*,struct nvmet_req*) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int) ; 
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvmet_execute_admin_connect(struct nvmet_req *req)
{
	struct nvmf_connect_command *c = &req->cmd->connect;
	struct nvmf_connect_data *d;
	struct nvmet_ctrl *ctrl = NULL;
	u16 status = 0;

	d = kmalloc(sizeof(*d), GFP_KERNEL);
	if (!d) {
		status = NVME_SC_INTERNAL;
		goto complete;
	}

	status = nvmet_copy_from_sgl(req, 0, d, sizeof(*d));
	if (status)
		goto out;

	/* zero out initial completion result, assign values as needed */
	req->rsp->result.u32 = 0;

	if (c->recfmt != 0) {
		pr_warn("invalid connect version (%d).\n",
			le16_to_cpu(c->recfmt));
		status = NVME_SC_CONNECT_FORMAT | NVME_SC_DNR;
		goto out;
	}

	if (unlikely(d->cntlid != cpu_to_le16(0xffff))) {
		pr_warn("connect attempt for invalid controller ID %#x\n",
			d->cntlid);
		status = NVME_SC_CONNECT_INVALID_PARAM | NVME_SC_DNR;
		req->rsp->result.u32 = IPO_IATTR_CONNECT_DATA(cntlid);
		goto out;
	}

	status = nvmet_alloc_ctrl(d->subsysnqn, d->hostnqn, req,
				  le32_to_cpu(c->kato), &ctrl);
	if (status)
		goto out;
	uuid_copy(&ctrl->hostid, &d->hostid);

	status = nvmet_install_queue(ctrl, req);
	if (status) {
		nvmet_ctrl_put(ctrl);
		goto out;
	}

	pr_info("creating controller %d for subsystem %s for NQN %s.\n",
		ctrl->cntlid, ctrl->subsys->subsysnqn, ctrl->hostnqn);
	req->rsp->result.u16 = cpu_to_le16(ctrl->cntlid);

out:
	kfree(d);
complete:
	nvmet_req_complete(req, status);
}