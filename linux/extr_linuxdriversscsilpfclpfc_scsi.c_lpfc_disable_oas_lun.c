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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct lpfc_name {int dummy; } ;
struct lpfc_hba {int /*<<< orphan*/  devicelock; int /*<<< orphan*/  luns; int /*<<< orphan*/  cfg_fof; } ;
struct lpfc_device_data {int oas_enabled; int /*<<< orphan*/  available; int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 struct lpfc_device_data* __lpfc_get_device_data (struct lpfc_hba*,int /*<<< orphan*/ *,struct lpfc_name*,struct lpfc_name*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_delete_device_data (struct lpfc_hba*,struct lpfc_device_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

bool
lpfc_disable_oas_lun(struct lpfc_hba *phba, struct lpfc_name *vport_wwpn,
		     struct lpfc_name *target_wwpn, uint64_t lun, uint8_t pri)
{

	struct lpfc_device_data *lun_info;
	unsigned long flags;

	if (unlikely(!phba) || !vport_wwpn || !target_wwpn ||
	    !phba->cfg_fof)
		return false;

	spin_lock_irqsave(&phba->devicelock, flags);

	/* Check to see if the lun is available. */
	lun_info = __lpfc_get_device_data(phba,
					  &phba->luns, vport_wwpn,
					  target_wwpn, lun);
	if (lun_info) {
		lun_info->oas_enabled = false;
		lun_info->priority = pri;
		if (!lun_info->available)
			lpfc_delete_device_data(phba, lun_info);
		spin_unlock_irqrestore(&phba->devicelock, flags);
		return true;
	}

	spin_unlock_irqrestore(&phba->devicelock, flags);
	return false;
}