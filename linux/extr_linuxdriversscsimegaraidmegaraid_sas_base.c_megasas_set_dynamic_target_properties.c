#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct scsi_device {int channel; scalar_t__ id; int /*<<< orphan*/  request_queue; struct MR_PRIV_DEVICE* hostdata; TYPE_1__* host; } ;
struct megasas_instance {int map_id; scalar_t__ fw_supported_vd_count; int pd_seq_map_id; void* task_abort_tmo; TYPE_5__* tgt_prop; int /*<<< orphan*/  max_reset_tmo; scalar_t__ use_seqnum_jbod_fp; struct fusion_context* ctrl_context; } ;
struct fusion_context {scalar_t__* pd_seq_sync; struct MR_DRV_RAID_MAP_ALL** ld_drv_map; } ;
struct MR_PRIV_DEVICE {void* task_abort_tmo; void* target_reset_tmo; int /*<<< orphan*/  is_tm_capable; } ;
struct MR_PD_CFG_SEQ_NUM_SYNC {TYPE_4__* seq; } ;
struct TYPE_7__ {scalar_t__ ldPiMode; int /*<<< orphan*/  tmCapable; } ;
struct MR_LD_RAID {TYPE_2__ capability; } ;
struct MR_DRV_RAID_MAP_ALL {int dummy; } ;
struct TYPE_10__ {scalar_t__ reset_tmo; } ;
struct TYPE_8__ {int /*<<< orphan*/  tmCapable; } ;
struct TYPE_9__ {TYPE_3__ capability; } ;
struct TYPE_6__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 void* MEGASAS_DEFAULT_TM_TIMEOUT ; 
 scalar_t__ MEGASAS_IS_LOGICAL (struct scsi_device*) ; 
 int MEGASAS_MAX_DEV_PER_CHANNEL ; 
 struct MR_LD_RAID* MR_LdRaidGet (scalar_t__,struct MR_DRV_RAID_MAP_ALL*) ; 
 scalar_t__ MR_PROT_INFO_TYPE_CONTROLLER ; 
 scalar_t__ MR_TargetIdToLdGet (scalar_t__,struct MR_DRV_RAID_MAP_ALL*) ; 
 int /*<<< orphan*/  blk_queue_update_dma_alignment (int /*<<< orphan*/ ,int) ; 
 struct megasas_instance* megasas_lookup_instance (int /*<<< orphan*/ ) ; 
 void* min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  u8 ; 

void megasas_set_dynamic_target_properties(struct scsi_device *sdev,
					   bool is_target_prop)
{
	u16 pd_index = 0, ld;
	u32 device_id;
	struct megasas_instance *instance;
	struct fusion_context *fusion;
	struct MR_PRIV_DEVICE *mr_device_priv_data;
	struct MR_PD_CFG_SEQ_NUM_SYNC *pd_sync;
	struct MR_LD_RAID *raid;
	struct MR_DRV_RAID_MAP_ALL *local_map_ptr;

	instance = megasas_lookup_instance(sdev->host->host_no);
	fusion = instance->ctrl_context;
	mr_device_priv_data = sdev->hostdata;

	if (!fusion || !mr_device_priv_data)
		return;

	if (MEGASAS_IS_LOGICAL(sdev)) {
		device_id = ((sdev->channel % 2) * MEGASAS_MAX_DEV_PER_CHANNEL)
					+ sdev->id;
		local_map_ptr = fusion->ld_drv_map[(instance->map_id & 1)];
		ld = MR_TargetIdToLdGet(device_id, local_map_ptr);
		if (ld >= instance->fw_supported_vd_count)
			return;
		raid = MR_LdRaidGet(ld, local_map_ptr);

		if (raid->capability.ldPiMode == MR_PROT_INFO_TYPE_CONTROLLER)
		blk_queue_update_dma_alignment(sdev->request_queue, 0x7);

		mr_device_priv_data->is_tm_capable =
			raid->capability.tmCapable;
	} else if (instance->use_seqnum_jbod_fp) {
		pd_index = (sdev->channel * MEGASAS_MAX_DEV_PER_CHANNEL) +
			sdev->id;
		pd_sync = (void *)fusion->pd_seq_sync
				[(instance->pd_seq_map_id - 1) & 1];
		mr_device_priv_data->is_tm_capable =
			pd_sync->seq[pd_index].capability.tmCapable;
	}

	if (is_target_prop && instance->tgt_prop->reset_tmo) {
		/*
		 * If FW provides a target reset timeout value, driver will use
		 * it. If not set, fallback to default values.
		 */
		mr_device_priv_data->target_reset_tmo =
			min_t(u8, instance->max_reset_tmo,
			      instance->tgt_prop->reset_tmo);
		mr_device_priv_data->task_abort_tmo = instance->task_abort_tmo;
	} else {
		mr_device_priv_data->target_reset_tmo =
						MEGASAS_DEFAULT_TM_TIMEOUT;
		mr_device_priv_data->task_abort_tmo =
						MEGASAS_DEFAULT_TM_TIMEOUT;
	}
}