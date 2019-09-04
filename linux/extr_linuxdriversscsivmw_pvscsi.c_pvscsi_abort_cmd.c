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
struct pvscsi_ctx {TYPE_2__* cmd; } ;
struct pvscsi_adapter {int dummy; } ;
struct PVSCSICmdDescAbortCmd {int /*<<< orphan*/  context; int /*<<< orphan*/  target; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {TYPE_1__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVSCSI_CMD_ABORT_CMD ; 
 int /*<<< orphan*/  pvscsi_map_context (struct pvscsi_adapter const*,struct pvscsi_ctx const*) ; 
 int /*<<< orphan*/  pvscsi_write_cmd_desc (struct pvscsi_adapter const*,int /*<<< orphan*/ ,struct PVSCSICmdDescAbortCmd*,int) ; 

__attribute__((used)) static void pvscsi_abort_cmd(const struct pvscsi_adapter *adapter,
			     const struct pvscsi_ctx *ctx)
{
	struct PVSCSICmdDescAbortCmd cmd = { 0 };

	cmd.target = ctx->cmd->device->id;
	cmd.context = pvscsi_map_context(adapter, ctx);

	pvscsi_write_cmd_desc(adapter, PVSCSI_CMD_ABORT_CMD, &cmd, sizeof(cmd));
}