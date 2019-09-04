#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* u32 ;
struct knav_reg_acc_command {int queue_num; int timer_config; void* list_dma; void* queue_mask; int /*<<< orphan*/  command; } ;
struct knav_acc_info {int list_entries; int pacing_mode; int timer_count; } ;
struct knav_range_info {int flags; int queue_base; struct knav_acc_channel* acc; int /*<<< orphan*/  num_queues; struct knav_acc_info acc_info; } ;
struct knav_device {int dummy; } ;
struct knav_acc_channel {scalar_t__* list_dma; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int ACC_CFG_MULTI_QUEUE ; 
 int ACC_LIST_ENTRY_TYPE ; 
 void* BIT (int /*<<< orphan*/ ) ; 
 int RANGE_MULTI_QUEUE ; 
 int /*<<< orphan*/  memset (struct knav_reg_acc_command*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void knav_acc_setup_cmd(struct knav_device *kdev,
				struct knav_range_info *range,
				struct knav_reg_acc_command *cmd,
				int queue)
{
	struct knav_acc_info *info = &range->acc_info;
	struct knav_acc_channel *acc;
	int queue_base;
	u32 queue_mask;

	if (range->flags & RANGE_MULTI_QUEUE) {
		acc = range->acc;
		queue_base = range->queue_base;
		queue_mask = BIT(range->num_queues) - 1;
	} else {
		acc = range->acc + queue;
		queue_base = range->queue_base + queue;
		queue_mask = 0;
	}

	memset(cmd, 0, sizeof(*cmd));
	cmd->command    = acc->channel;
	cmd->queue_mask = queue_mask;
	cmd->list_dma   = (u32)acc->list_dma[0];
	cmd->queue_num  = info->list_entries << 16;
	cmd->queue_num |= queue_base;

	cmd->timer_config = ACC_LIST_ENTRY_TYPE << 18;
	if (range->flags & RANGE_MULTI_QUEUE)
		cmd->timer_config |= ACC_CFG_MULTI_QUEUE;
	cmd->timer_config |= info->pacing_mode << 16;
	cmd->timer_config |= info->timer_count;
}