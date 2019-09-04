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
struct megasas_instance {struct fusion_context* ctrl_context; } ;
struct megasas_header {int cmd_status; } ;
struct megasas_cmd {TYPE_1__* frame; } ;
struct fusion_context {int dummy; } ;
struct TYPE_2__ {struct megasas_header hdr; } ;

/* Variables and functions */
 int DCMD_FAILED ; 
 int DCMD_SUCCESS ; 
 int DCMD_TIMEOUT ; 
 int MFI_STAT_INVALID_STATUS ; 
 int MFI_STAT_OK ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rmb () ; 

int
wait_and_poll(struct megasas_instance *instance, struct megasas_cmd *cmd,
	int seconds)
{
	int i;
	struct megasas_header *frame_hdr = &cmd->frame->hdr;
	struct fusion_context *fusion;

	u32 msecs = seconds * 1000;

	fusion = instance->ctrl_context;
	/*
	 * Wait for cmd_status to change
	 */
	for (i = 0; (i < msecs) && (frame_hdr->cmd_status == 0xff); i += 20) {
		rmb();
		msleep(20);
	}

	if (frame_hdr->cmd_status == MFI_STAT_INVALID_STATUS)
		return DCMD_TIMEOUT;
	else if (frame_hdr->cmd_status == MFI_STAT_OK)
		return DCMD_SUCCESS;
	else
		return DCMD_FAILED;
}