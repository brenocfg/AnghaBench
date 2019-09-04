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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {scalar_t__ cfg_oas_priority; scalar_t__ cfg_XLanePriority; int /*<<< orphan*/  cfg_oas_lun_state; int /*<<< orphan*/  cfg_oas_tgt_wwpn; int /*<<< orphan*/  cfg_oas_vpt_wwpn; int /*<<< orphan*/  cfg_fof; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EFAULT ; 
 size_t EINVAL ; 
 size_t EPERM ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_INIT ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 size_t lpfc_oas_lun_state_change (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ wwn_to_u64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
lpfc_oas_lun_store(struct device *dev, struct device_attribute *attr,
		   const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct lpfc_hba *phba = ((struct lpfc_vport *)shost->hostdata)->phba;
	uint64_t scsi_lun;
	uint32_t pri;
	ssize_t rc;

	if (!phba->cfg_fof)
		return -EPERM;

	if (wwn_to_u64(phba->cfg_oas_vpt_wwpn) == 0)
		return -EFAULT;

	if (wwn_to_u64(phba->cfg_oas_tgt_wwpn) == 0)
		return -EFAULT;

	if (!isdigit(buf[0]))
		return -EINVAL;

	if (sscanf(buf, "0x%llx", &scsi_lun) != 1)
		return -EINVAL;

	pri = phba->cfg_oas_priority;
	if (pri == 0)
		pri = phba->cfg_XLanePriority;

	lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"3372 Try to set vport 0x%llx target 0x%llx lun:0x%llx "
			"priority 0x%x with oas state %d\n",
			wwn_to_u64(phba->cfg_oas_vpt_wwpn),
			wwn_to_u64(phba->cfg_oas_tgt_wwpn), scsi_lun,
			pri, phba->cfg_oas_lun_state);

	rc = lpfc_oas_lun_state_change(phba, phba->cfg_oas_vpt_wwpn,
				       phba->cfg_oas_tgt_wwpn, scsi_lun,
				       phba->cfg_oas_lun_state, pri);
	if (rc)
		return rc;

	return count;
}