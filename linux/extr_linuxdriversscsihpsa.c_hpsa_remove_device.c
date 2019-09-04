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
struct hpsa_scsi_dev_t {int removed; int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  bus; } ;
struct ctlr_info {int /*<<< orphan*/  scsi_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  hpsa_remove_sas_device (struct hpsa_scsi_dev_t*) ; 
 int /*<<< orphan*/  hpsa_show_dev_msg (int /*<<< orphan*/ ,struct ctlr_info*,struct hpsa_scsi_dev_t*,char*) ; 
 int /*<<< orphan*/  hpsa_wait_for_outstanding_commands_for_dev (struct ctlr_info*,struct hpsa_scsi_dev_t*) ; 
 scalar_t__ is_logical_device (struct hpsa_scsi_dev_t*) ; 
 struct scsi_device* scsi_device_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_device_put (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_remove_device (struct scsi_device*) ; 

__attribute__((used)) static void hpsa_remove_device(struct ctlr_info *h,
			struct hpsa_scsi_dev_t *device)
{
	struct scsi_device *sdev = NULL;

	if (!h->scsi_host)
		return;

	/*
	 * Allow for commands to drain
	 */
	device->removed = 1;
	hpsa_wait_for_outstanding_commands_for_dev(h, device);

	if (is_logical_device(device)) { /* RAID */
		sdev = scsi_device_lookup(h->scsi_host, device->bus,
						device->target, device->lun);
		if (sdev) {
			scsi_remove_device(sdev);
			scsi_device_put(sdev);
		} else {
			/*
			 * We don't expect to get here.  Future commands
			 * to this device will get a selection timeout as
			 * if the device were gone.
			 */
			hpsa_show_dev_msg(KERN_WARNING, h, device,
					"didn't find device for removal.");
		}
	} else { /* HBA */

		hpsa_remove_sas_device(device);
	}
}