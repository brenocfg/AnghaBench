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
struct nvme_ctrl {int /*<<< orphan*/  admin_q; } ;
struct TYPE_2__ {int /*<<< orphan*/  endir; int /*<<< orphan*/  tdtype; int /*<<< orphan*/  dtype; int /*<<< orphan*/  doper; int /*<<< orphan*/  nsid; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_1__ directive; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_DIR_ENDIR ; 
 int /*<<< orphan*/  NVME_DIR_IDENTIFY ; 
 int /*<<< orphan*/  NVME_DIR_SND_ID_OP_ENABLE ; 
 int /*<<< orphan*/  NVME_DIR_STREAMS ; 
 int /*<<< orphan*/  NVME_NSID_ALL ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_admin_directive_send ; 
 int nvme_submit_sync_cmd (int /*<<< orphan*/ ,struct nvme_command*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_toggle_streams(struct nvme_ctrl *ctrl, bool enable)
{
	struct nvme_command c;

	memset(&c, 0, sizeof(c));

	c.directive.opcode = nvme_admin_directive_send;
	c.directive.nsid = cpu_to_le32(NVME_NSID_ALL);
	c.directive.doper = NVME_DIR_SND_ID_OP_ENABLE;
	c.directive.dtype = NVME_DIR_IDENTIFY;
	c.directive.tdtype = NVME_DIR_STREAMS;
	c.directive.endir = enable ? NVME_DIR_ENDIR : 0;

	return nvme_submit_sync_cmd(ctrl->admin_q, &c, NULL, 0);
}