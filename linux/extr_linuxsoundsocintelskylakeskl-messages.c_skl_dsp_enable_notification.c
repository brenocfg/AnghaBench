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
typedef  int /*<<< orphan*/  u32 ;
struct skl_sst {int /*<<< orphan*/  ipc; } ;
struct skl_ipc_large_config_msg {int param_data_size; int /*<<< orphan*/  large_param_id; int /*<<< orphan*/  member_0; } ;
struct notification_mask {int enable; int /*<<< orphan*/  notify; } ;
typedef  int /*<<< orphan*/  mask ;

/* Variables and functions */
 int /*<<< orphan*/  NOTIFICATION_MASK ; 
 int /*<<< orphan*/  NOTIFICATION_PARAM_ID ; 
 int /*<<< orphan*/  skl_ipc_set_large_config (int /*<<< orphan*/ *,struct skl_ipc_large_config_msg*,int /*<<< orphan*/ *) ; 

void skl_dsp_enable_notification(struct skl_sst *ctx, bool enable)
{
	struct notification_mask mask;
	struct skl_ipc_large_config_msg	msg = {0};

	mask.notify = NOTIFICATION_MASK;
	mask.enable = enable;

	msg.large_param_id = NOTIFICATION_PARAM_ID;
	msg.param_data_size = sizeof(mask);

	skl_ipc_set_large_config(&ctx->ipc, &msg, (u32 *)&mask);
}