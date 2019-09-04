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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dtype; int /*<<< orphan*/  doper; void* numd; void* nsid; int /*<<< orphan*/  opcode; } ;
struct streams_directive_params {TYPE_1__ directive; } ;
struct nvme_ctrl {int /*<<< orphan*/  admin_q; } ;
struct nvme_command {TYPE_1__ directive; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_DIR_RCV_ST_OP_PARAM ; 
 int /*<<< orphan*/  NVME_DIR_STREAMS ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (struct streams_directive_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_admin_directive_recv ; 
 int nvme_submit_sync_cmd (int /*<<< orphan*/ ,struct streams_directive_params*,struct streams_directive_params*,int) ; 

__attribute__((used)) static int nvme_get_stream_params(struct nvme_ctrl *ctrl,
				  struct streams_directive_params *s, u32 nsid)
{
	struct nvme_command c;

	memset(&c, 0, sizeof(c));
	memset(s, 0, sizeof(*s));

	c.directive.opcode = nvme_admin_directive_recv;
	c.directive.nsid = cpu_to_le32(nsid);
	c.directive.numd = cpu_to_le32((sizeof(*s) >> 2) - 1);
	c.directive.doper = NVME_DIR_RCV_ST_OP_PARAM;
	c.directive.dtype = NVME_DIR_STREAMS;

	return nvme_submit_sync_cmd(ctrl->admin_q, &c, s, sizeof(*s));
}