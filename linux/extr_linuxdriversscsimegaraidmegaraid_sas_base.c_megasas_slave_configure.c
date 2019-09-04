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
typedef  size_t u16 ;
struct scsi_device {scalar_t__ type; int channel; size_t id; TYPE_1__* host; } ;
struct megasas_instance {int /*<<< orphan*/  reset_mutex; scalar_t__ nvme_page_size; scalar_t__ tgt_prop; scalar_t__ pd_info; TYPE_2__* pd_list; scalar_t__ pd_list_not_supported; } ;
struct TYPE_4__ {scalar_t__ driveState; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int DCMD_FAILED ; 
 int DCMD_SUCCESS ; 
 int ENXIO ; 
 int /*<<< orphan*/  MEGASAS_IS_LOGICAL (struct scsi_device*) ; 
 int MEGASAS_MAX_DEV_PER_CHANNEL ; 
 scalar_t__ MR_PD_STATE_SYSTEM ; 
 scalar_t__ TYPE_DISK ; 
 int /*<<< orphan*/  megasas_get_pd_info (struct megasas_instance*,struct scsi_device*) ; 
 int megasas_get_target_prop (struct megasas_instance*,struct scsi_device*) ; 
 struct megasas_instance* megasas_lookup_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  megasas_set_dynamic_target_properties (struct scsi_device*,int) ; 
 int /*<<< orphan*/  megasas_set_static_target_properties (struct scsi_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int megasas_slave_configure(struct scsi_device *sdev)
{
	u16 pd_index = 0;
	struct megasas_instance *instance;
	int ret_target_prop = DCMD_FAILED;
	bool is_target_prop = false;

	instance = megasas_lookup_instance(sdev->host->host_no);
	if (instance->pd_list_not_supported) {
		if (!MEGASAS_IS_LOGICAL(sdev) && sdev->type == TYPE_DISK) {
			pd_index = (sdev->channel * MEGASAS_MAX_DEV_PER_CHANNEL) +
				sdev->id;
			if (instance->pd_list[pd_index].driveState !=
				MR_PD_STATE_SYSTEM)
				return -ENXIO;
		}
	}

	mutex_lock(&instance->reset_mutex);
	/* Send DCMD to Firmware and cache the information */
	if ((instance->pd_info) && !MEGASAS_IS_LOGICAL(sdev))
		megasas_get_pd_info(instance, sdev);

	/* Some ventura firmware may not have instance->nvme_page_size set.
	 * Do not send MR_DCMD_DRV_GET_TARGET_PROP
	 */
	if ((instance->tgt_prop) && (instance->nvme_page_size))
		ret_target_prop = megasas_get_target_prop(instance, sdev);

	is_target_prop = (ret_target_prop == DCMD_SUCCESS) ? true : false;
	megasas_set_static_target_properties(sdev, is_target_prop);

	/* This sdev property may change post OCR */
	megasas_set_dynamic_target_properties(sdev, is_target_prop);

	mutex_unlock(&instance->reset_mutex);

	return 0;
}