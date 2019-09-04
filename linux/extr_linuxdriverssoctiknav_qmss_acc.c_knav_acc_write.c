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
struct knav_reg_acc_command {int /*<<< orphan*/  command; int /*<<< orphan*/  queue_mask; int /*<<< orphan*/  list_dma; int /*<<< orphan*/  queue_num; int /*<<< orphan*/  timer_config; } ;
struct knav_pdsp_info {TYPE_1__* acc_command; } ;
struct knav_device {int /*<<< orphan*/  dev; } ;
typedef  enum knav_acc_result { ____Placeholder_knav_acc_result } knav_acc_result ;
struct TYPE_2__ {int /*<<< orphan*/  command; int /*<<< orphan*/  queue_mask; int /*<<< orphan*/  list_dma; int /*<<< orphan*/  queue_num; int /*<<< orphan*/  timer_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl_relaxed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum knav_acc_result
knav_acc_write(struct knav_device *kdev, struct knav_pdsp_info *pdsp,
		struct knav_reg_acc_command *cmd)
{
	u32 result;

	dev_dbg(kdev->dev, "acc command %08x %08x %08x %08x %08x\n",
		cmd->command, cmd->queue_mask, cmd->list_dma,
		cmd->queue_num, cmd->timer_config);

	writel_relaxed(cmd->timer_config, &pdsp->acc_command->timer_config);
	writel_relaxed(cmd->queue_num, &pdsp->acc_command->queue_num);
	writel_relaxed(cmd->list_dma, &pdsp->acc_command->list_dma);
	writel_relaxed(cmd->queue_mask, &pdsp->acc_command->queue_mask);
	writel_relaxed(cmd->command, &pdsp->acc_command->command);

	/* wait for the command to clear */
	do {
		result = readl_relaxed(&pdsp->acc_command->command);
	} while ((result >> 8) & 0xff);

	return (result >> 24) & 0xff;
}