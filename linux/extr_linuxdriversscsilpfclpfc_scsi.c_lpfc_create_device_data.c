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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_name {int dummy; } ;
struct lpfc_hba {int /*<<< orphan*/  device_data_mem_pool; int /*<<< orphan*/  cfg_fof; } ;
struct TYPE_2__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  target_wwpn; int /*<<< orphan*/  vport_wwpn; } ;
struct lpfc_device_data {int oas_enabled; int available; int /*<<< orphan*/  priority; TYPE_1__ device_id; int /*<<< orphan*/ * rport_data; int /*<<< orphan*/  listentry; } ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct lpfc_name*,int) ; 
 struct lpfc_device_data* mempool_alloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

struct lpfc_device_data*
lpfc_create_device_data(struct lpfc_hba *phba, struct lpfc_name *vport_wwpn,
			struct lpfc_name *target_wwpn, uint64_t lun,
			uint32_t pri, bool atomic_create)
{

	struct lpfc_device_data *lun_info;
	int memory_flags;

	if (unlikely(!phba) || !vport_wwpn || !target_wwpn  ||
	    !(phba->cfg_fof))
		return NULL;

	/* Attempt to create the device data to contain lun info */

	if (atomic_create)
		memory_flags = GFP_ATOMIC;
	else
		memory_flags = GFP_KERNEL;
	lun_info = mempool_alloc(phba->device_data_mem_pool, memory_flags);
	if (!lun_info)
		return NULL;
	INIT_LIST_HEAD(&lun_info->listentry);
	lun_info->rport_data  = NULL;
	memcpy(&lun_info->device_id.vport_wwpn, vport_wwpn,
	       sizeof(struct lpfc_name));
	memcpy(&lun_info->device_id.target_wwpn, target_wwpn,
	       sizeof(struct lpfc_name));
	lun_info->device_id.lun = lun;
	lun_info->oas_enabled = false;
	lun_info->priority = pri;
	lun_info->available = false;
	return lun_info;
}