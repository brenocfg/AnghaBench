#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct nvmet_subsys {int /*<<< orphan*/  lock; } ;
struct nvmet_req {TYPE_5__* ns; TYPE_4__* cmd; TYPE_2__* sq; } ;
struct TYPE_12__ {struct nvmet_subsys* subsys; } ;
struct TYPE_11__ {int readonly; int /*<<< orphan*/  nsid; } ;
struct TYPE_9__ {int /*<<< orphan*/  nsid; } ;
struct TYPE_7__ {int /*<<< orphan*/ * cdw10; } ;
struct TYPE_10__ {TYPE_3__ rw; TYPE_1__ common; } ;
struct TYPE_8__ {TYPE_6__* ctrl; } ;

/* Variables and functions */
#define  NVME_NS_NO_WRITE_PROTECT 129 
#define  NVME_NS_WRITE_PROTECT 128 
 scalar_t__ NVME_SC_FEATURE_NOT_CHANGEABLE ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_5__* nvmet_find_namespace (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_ns_changed (struct nvmet_subsys*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvmet_write_protect_flush_sync (struct nvmet_req*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u16 nvmet_set_feat_write_protect(struct nvmet_req *req)
{
	u32 write_protect = le32_to_cpu(req->cmd->common.cdw10[1]);
	struct nvmet_subsys *subsys = req->sq->ctrl->subsys;
	u16 status = NVME_SC_FEATURE_NOT_CHANGEABLE;

	req->ns = nvmet_find_namespace(req->sq->ctrl, req->cmd->rw.nsid);
	if (unlikely(!req->ns))
		return status;

	mutex_lock(&subsys->lock);
	switch (write_protect) {
	case NVME_NS_WRITE_PROTECT:
		req->ns->readonly = true;
		status = nvmet_write_protect_flush_sync(req);
		if (status)
			req->ns->readonly = false;
		break;
	case NVME_NS_NO_WRITE_PROTECT:
		req->ns->readonly = false;
		status = 0;
		break;
	default:
		break;
	}

	if (!status)
		nvmet_ns_changed(subsys, req->ns->nsid);
	mutex_unlock(&subsys->lock);
	return status;
}