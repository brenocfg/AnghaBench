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
typedef  union MPI2_REPLY_DESCRIPTORS_UNION {int dummy; } MPI2_REPLY_DESCRIPTORS_UNION ;
typedef  union MEGASAS_REQUEST_DESCRIPTOR_UNION {int dummy; } MEGASAS_REQUEST_DESCRIPTOR_UNION ;
typedef  int u16 ;
struct megasas_instance {int max_fw_cmds; scalar_t__ adapter_type; int max_mpt_cmds; scalar_t__ cur_can_queue; TYPE_1__* host; scalar_t__ max_scsi_cmds; struct fusion_context* ctrl_context; } ;
struct fusion_context {int reply_q_depth; int request_alloc_sz; int reply_alloc_sz; int io_frames_alloc_sz; } ;
struct TYPE_2__ {scalar_t__ can_queue; } ;

/* Variables and functions */
 scalar_t__ MEGASAS_FUSION_INTERNAL_CMDS ; 
 scalar_t__ MEGASAS_FUSION_IOCTL_CMDS ; 
 int MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE ; 
 int RAID_1_PEER_CMDS ; 
 scalar_t__ VENTURA_SERIES ; 

__attribute__((used)) static inline
void megasas_configure_queue_sizes(struct megasas_instance *instance)
{
	struct fusion_context *fusion;
	u16 max_cmd;

	fusion = instance->ctrl_context;
	max_cmd = instance->max_fw_cmds;

	if (instance->adapter_type == VENTURA_SERIES)
		instance->max_mpt_cmds = instance->max_fw_cmds * RAID_1_PEER_CMDS;
	else
		instance->max_mpt_cmds = instance->max_fw_cmds;

	instance->max_scsi_cmds = instance->max_fw_cmds -
			(MEGASAS_FUSION_INTERNAL_CMDS +
			MEGASAS_FUSION_IOCTL_CMDS);
	instance->cur_can_queue = instance->max_scsi_cmds;
	instance->host->can_queue = instance->cur_can_queue;

	fusion->reply_q_depth = 2 * ((max_cmd + 1 + 15) / 16) * 16;

	fusion->request_alloc_sz = sizeof(union MEGASAS_REQUEST_DESCRIPTOR_UNION) *
					  instance->max_mpt_cmds;
	fusion->reply_alloc_sz = sizeof(union MPI2_REPLY_DESCRIPTORS_UNION) *
					(fusion->reply_q_depth);
	fusion->io_frames_alloc_sz = MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE +
		(MEGA_MPI2_RAID_DEFAULT_IO_FRAME_SIZE
		 * (instance->max_mpt_cmds + 1)); /* Extra 1 for SMID 0 */
}