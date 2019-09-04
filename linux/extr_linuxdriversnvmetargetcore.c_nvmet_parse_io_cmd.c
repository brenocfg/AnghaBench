#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct nvmet_req {TYPE_3__* ns; int /*<<< orphan*/  port; TYPE_2__* sq; struct nvme_command* cmd; } ;
struct TYPE_5__ {int /*<<< orphan*/  nsid; } ;
struct nvme_command {TYPE_1__ rw; } ;
struct TYPE_7__ {scalar_t__ file; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int NVME_SC_DNR ; 
 int NVME_SC_INVALID_NS ; 
 int nvmet_bdev_parse_io_cmd (struct nvmet_req*) ; 
 int nvmet_check_ana_state (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int nvmet_check_ctrl_status (struct nvmet_req*,struct nvme_command*) ; 
 int nvmet_file_parse_io_cmd (struct nvmet_req*) ; 
 TYPE_3__* nvmet_find_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvmet_io_cmd_check_access (struct nvmet_req*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u16 nvmet_parse_io_cmd(struct nvmet_req *req)
{
	struct nvme_command *cmd = req->cmd;
	u16 ret;

	ret = nvmet_check_ctrl_status(req, cmd);
	if (unlikely(ret))
		return ret;

	req->ns = nvmet_find_namespace(req->sq->ctrl, cmd->rw.nsid);
	if (unlikely(!req->ns))
		return NVME_SC_INVALID_NS | NVME_SC_DNR;
	ret = nvmet_check_ana_state(req->port, req->ns);
	if (unlikely(ret))
		return ret;
	ret = nvmet_io_cmd_check_access(req);
	if (unlikely(ret))
		return ret;

	if (req->ns->file)
		return nvmet_file_parse_io_cmd(req);
	else
		return nvmet_bdev_parse_io_cmd(req);
}