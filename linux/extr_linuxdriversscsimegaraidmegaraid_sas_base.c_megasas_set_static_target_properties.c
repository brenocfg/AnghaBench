#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct scsi_device {int channel; scalar_t__ id; int /*<<< orphan*/  request_queue; struct MR_PRIV_DEVICE* hostdata; TYPE_1__* host; } ;
struct megasas_instance {scalar_t__ nvme_page_size; TYPE_3__* tgt_prop; TYPE_2__* host; } ;
struct MR_PRIV_DEVICE {int interface_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_io_size_kb; int /*<<< orphan*/  device_qdepth; } ;
struct TYPE_5__ {scalar_t__ can_queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ MEGASAS_DEFAULT_CMD_PER_LUN ; 
 int MEGASAS_MAX_DEV_PER_CHANNEL ; 
 scalar_t__ MEGASAS_NVME_QD ; 
 scalar_t__ MEGASAS_SAS_QD ; 
 scalar_t__ MEGASAS_SATA_QD ; 
 scalar_t__ MR_DEFAULT_NVME_MDTS_KB ; 
#define  NVME_PD 130 
#define  SAS_PD 129 
#define  SATA_PD 128 
 int /*<<< orphan*/  blk_queue_rq_timeout (int /*<<< orphan*/ ,int) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct megasas_instance* megasas_lookup_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  megasas_set_nvme_device_properties (struct scsi_device*,scalar_t__) ; 
 int scmd_timeout ; 
 int /*<<< orphan*/  scsi_change_queue_depth (struct scsi_device*,scalar_t__) ; 

__attribute__((used)) static void megasas_set_static_target_properties(struct scsi_device *sdev,
						 bool is_target_prop)
{
	u16	target_index = 0;
	u8 interface_type;
	u32 device_qd = MEGASAS_DEFAULT_CMD_PER_LUN;
	u32 max_io_size_kb = MR_DEFAULT_NVME_MDTS_KB;
	u32 tgt_device_qd;
	struct megasas_instance *instance;
	struct MR_PRIV_DEVICE *mr_device_priv_data;

	instance = megasas_lookup_instance(sdev->host->host_no);
	mr_device_priv_data = sdev->hostdata;
	interface_type  = mr_device_priv_data->interface_type;

	/*
	 * The RAID firmware may require extended timeouts.
	 */
	blk_queue_rq_timeout(sdev->request_queue, scmd_timeout * HZ);

	target_index = (sdev->channel * MEGASAS_MAX_DEV_PER_CHANNEL) + sdev->id;

	switch (interface_type) {
	case SAS_PD:
		device_qd = MEGASAS_SAS_QD;
		break;
	case SATA_PD:
		device_qd = MEGASAS_SATA_QD;
		break;
	case NVME_PD:
		device_qd = MEGASAS_NVME_QD;
		break;
	}

	if (is_target_prop) {
		tgt_device_qd = le32_to_cpu(instance->tgt_prop->device_qdepth);
		if (tgt_device_qd &&
		    (tgt_device_qd <= instance->host->can_queue))
			device_qd = tgt_device_qd;

		/* max_io_size_kb will be set to non zero for
		 * nvme based vd and syspd.
		 */
		max_io_size_kb = le32_to_cpu(instance->tgt_prop->max_io_size_kb);
	}

	if (instance->nvme_page_size && max_io_size_kb)
		megasas_set_nvme_device_properties(sdev, (max_io_size_kb << 10));

	scsi_change_queue_depth(sdev, device_qd);

}