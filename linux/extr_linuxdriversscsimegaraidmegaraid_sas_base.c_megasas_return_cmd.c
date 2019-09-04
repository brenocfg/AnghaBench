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
typedef  size_t u32 ;
struct TYPE_7__ {int /*<<< orphan*/  next; } ;
struct megasas_instance {size_t max_scsi_cmds; int /*<<< orphan*/  mfi_pool_lock; TYPE_3__ cmd_pool; int /*<<< orphan*/  mfi_frame_size; struct fusion_context* ctrl_context; } ;
struct megasas_cmd_fusion {int dummy; } ;
struct megasas_cmd {int flags; size_t index; int /*<<< orphan*/  list; TYPE_4__* frame; scalar_t__ frame_count; int /*<<< orphan*/ * scmd; } ;
struct fusion_context {struct megasas_cmd_fusion** cmd_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_5__ {int /*<<< orphan*/  context; } ;
struct TYPE_8__ {TYPE_2__ hdr; TYPE_1__ io; } ;

/* Variables and functions */
 int DRV_DCMD_POLLED_MODE ; 
 int /*<<< orphan*/  MFI_CMD_INVALID ; 
 int /*<<< orphan*/  cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  megasas_return_cmd_fusion (struct megasas_instance*,struct megasas_cmd_fusion*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ reset_devices ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
megasas_return_cmd(struct megasas_instance *instance, struct megasas_cmd *cmd)
{
	unsigned long flags;
	u32 blk_tags;
	struct megasas_cmd_fusion *cmd_fusion;
	struct fusion_context *fusion = instance->ctrl_context;

	/* This flag is used only for fusion adapter.
	 * Wait for Interrupt for Polled mode DCMD
	 */
	if (cmd->flags & DRV_DCMD_POLLED_MODE)
		return;

	spin_lock_irqsave(&instance->mfi_pool_lock, flags);

	if (fusion) {
		blk_tags = instance->max_scsi_cmds + cmd->index;
		cmd_fusion = fusion->cmd_list[blk_tags];
		megasas_return_cmd_fusion(instance, cmd_fusion);
	}
	cmd->scmd = NULL;
	cmd->frame_count = 0;
	cmd->flags = 0;
	memset(cmd->frame, 0, instance->mfi_frame_size);
	cmd->frame->io.context = cpu_to_le32(cmd->index);
	if (!fusion && reset_devices)
		cmd->frame->hdr.cmd = MFI_CMD_INVALID;
	list_add(&cmd->list, (&instance->cmd_pool)->next);

	spin_unlock_irqrestore(&instance->mfi_pool_lock, flags);

}