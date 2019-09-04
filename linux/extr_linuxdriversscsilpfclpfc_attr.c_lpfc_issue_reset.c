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
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {int (* lpfc_selective_reset ) (struct lpfc_hba*) ;int /*<<< orphan*/  cfg_enable_hba_reset; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int stub1 (struct lpfc_hba*) ; 

__attribute__((used)) static ssize_t
lpfc_issue_reset(struct device *dev, struct device_attribute *attr,
		 const char *buf, size_t count)
{
	struct Scsi_Host  *shost = class_to_shost(dev);
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;
	int status = -EINVAL;

	if (!phba->cfg_enable_hba_reset)
		return -EACCES;

	if (strncmp(buf, "selective", sizeof("selective") - 1) == 0)
		status = phba->lpfc_selective_reset(phba);

	if (status == 0)
		return strlen(buf);
	else
		return status;
}