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
struct scsi_device {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct class_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_device_enclosure (struct scsi_device*) ; 
 int /*<<< orphan*/  ses_intf_remove_component (struct scsi_device*) ; 
 int /*<<< orphan*/  ses_intf_remove_enclosure (struct scsi_device*) ; 
 struct scsi_device* to_scsi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ses_intf_remove(struct device *cdev,
			    struct class_interface *intf)
{
	struct scsi_device *sdev = to_scsi_device(cdev->parent);

	if (!scsi_device_enclosure(sdev))
		ses_intf_remove_component(sdev);
	else
		ses_intf_remove_enclosure(sdev);
}