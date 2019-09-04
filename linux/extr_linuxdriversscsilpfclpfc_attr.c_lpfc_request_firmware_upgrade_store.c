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
struct lpfc_hba {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  RUN_FW_UPGRADE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int lpfc_sli4_request_firmware_update (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,int*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static ssize_t
lpfc_request_firmware_upgrade_store(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct lpfc_vport *vport = (struct lpfc_vport *)shost->hostdata;
	struct lpfc_hba *phba = vport->phba;
	int val = 0, rc = -EINVAL;

	/* Sanity check on user data */
	if (!isdigit(buf[0]))
		return -EINVAL;
	if (sscanf(buf, "%i", &val) != 1)
		return -EINVAL;
	if (val != 1)
		return -EINVAL;

	rc = lpfc_sli4_request_firmware_update(phba, RUN_FW_UPGRADE);
	if (rc)
		rc = -EPERM;
	else
		rc = strlen(buf);
	return rc;
}