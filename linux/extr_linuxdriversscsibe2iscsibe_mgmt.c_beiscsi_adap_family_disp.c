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
typedef  int uint16_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct beiscsi_hba {TYPE_1__* pcidev; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
#define  BE_DEVICE_ID1 133 
#define  BE_DEVICE_ID2 132 
#define  OC_DEVICE_ID1 131 
#define  OC_DEVICE_ID2 130 
#define  OC_DEVICE_ID3 129 
#define  OC_SKH_ID1 128 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 struct beiscsi_hba* iscsi_host_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

ssize_t
beiscsi_adap_family_disp(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	uint16_t dev_id = 0;
	struct Scsi_Host *shost = class_to_shost(dev);
	struct beiscsi_hba *phba = iscsi_host_priv(shost);

	dev_id = phba->pcidev->device;
	switch (dev_id) {
	case BE_DEVICE_ID1:
	case OC_DEVICE_ID1:
	case OC_DEVICE_ID2:
		return snprintf(buf, PAGE_SIZE,
				"Obsolete/Unsupported BE2 Adapter Family\n");
		break;
	case BE_DEVICE_ID2:
	case OC_DEVICE_ID3:
		return snprintf(buf, PAGE_SIZE, "BE3-R Adapter Family\n");
		break;
	case OC_SKH_ID1:
		return snprintf(buf, PAGE_SIZE, "Skyhawk-R Adapter Family\n");
		break;
	default:
		return snprintf(buf, PAGE_SIZE,
				"Unknown Adapter Family: 0x%x\n", dev_id);
		break;
	}
}