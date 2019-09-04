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
struct scsi_device {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALUA_DH_NAME ; 
 int /*<<< orphan*/  KERN_INFO ; 
#define  TPGS_MODE_EXPLICIT 130 
#define  TPGS_MODE_IMPLICIT 129 
#define  TPGS_MODE_NONE 128 
 scalar_t__ TYPE_DISK ; 
 int scsi_device_tpgs (struct scsi_device*) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int alua_check_tpgs(struct scsi_device *sdev)
{
	int tpgs = TPGS_MODE_NONE;

	/*
	 * ALUA support for non-disk devices is fraught with
	 * difficulties, so disable it for now.
	 */
	if (sdev->type != TYPE_DISK) {
		sdev_printk(KERN_INFO, sdev,
			    "%s: disable for non-disk devices\n",
			    ALUA_DH_NAME);
		return tpgs;
	}

	tpgs = scsi_device_tpgs(sdev);
	switch (tpgs) {
	case TPGS_MODE_EXPLICIT|TPGS_MODE_IMPLICIT:
		sdev_printk(KERN_INFO, sdev,
			    "%s: supports implicit and explicit TPGS\n",
			    ALUA_DH_NAME);
		break;
	case TPGS_MODE_EXPLICIT:
		sdev_printk(KERN_INFO, sdev, "%s: supports explicit TPGS\n",
			    ALUA_DH_NAME);
		break;
	case TPGS_MODE_IMPLICIT:
		sdev_printk(KERN_INFO, sdev, "%s: supports implicit TPGS\n",
			    ALUA_DH_NAME);
		break;
	case TPGS_MODE_NONE:
		sdev_printk(KERN_INFO, sdev, "%s: not supported\n",
			    ALUA_DH_NAME);
		break;
	default:
		sdev_printk(KERN_INFO, sdev,
			    "%s: unsupported TPGS setting %d\n",
			    ALUA_DH_NAME, tpgs);
		tpgs = TPGS_MODE_NONE;
		break;
	}

	return tpgs;
}