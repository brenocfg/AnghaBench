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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct nvmet_subsys {int /*<<< orphan*/  lock; } ;
struct nvmet_req {TYPE_4__* ns; TYPE_2__* cmd; TYPE_3__* sq; } ;
struct TYPE_10__ {struct nvmet_subsys* subsys; } ;
struct TYPE_9__ {int readonly; } ;
struct TYPE_8__ {TYPE_5__* ctrl; } ;
struct TYPE_6__ {int /*<<< orphan*/  nsid; } ;
struct TYPE_7__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_NS_NO_WRITE_PROTECT ; 
 int /*<<< orphan*/  NVME_NS_WRITE_PROTECT ; 
 int NVME_SC_DNR ; 
 int NVME_SC_INVALID_NS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_4__* nvmet_find_namespace (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_set_result (struct nvmet_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 nvmet_get_feat_write_protect(struct nvmet_req *req)
{
	struct nvmet_subsys *subsys = req->sq->ctrl->subsys;
	u32 result;

	req->ns = nvmet_find_namespace(req->sq->ctrl, req->cmd->common.nsid);
	if (!req->ns)
		return NVME_SC_INVALID_NS | NVME_SC_DNR;

	mutex_lock(&subsys->lock);
	if (req->ns->readonly == true)
		result = NVME_NS_WRITE_PROTECT;
	else
		result = NVME_NS_NO_WRITE_PROTECT;
	nvmet_set_result(req, result);
	mutex_unlock(&subsys->lock);

	return 0;
}