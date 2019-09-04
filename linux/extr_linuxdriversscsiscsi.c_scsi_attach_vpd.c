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
struct scsi_vpd {int len; int* data; } ;
struct scsi_device {int /*<<< orphan*/  vpd_pg83; int /*<<< orphan*/  vpd_pg80; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct scsi_vpd*) ; 
 int /*<<< orphan*/  scsi_device_supports_vpd (struct scsi_device*) ; 
 struct scsi_vpd* scsi_get_vpd_buf (struct scsi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_update_vpd_page (struct scsi_device*,int,int /*<<< orphan*/ *) ; 

void scsi_attach_vpd(struct scsi_device *sdev)
{
	int i;
	struct scsi_vpd *vpd_buf;

	if (!scsi_device_supports_vpd(sdev))
		return;

	/* Ask for all the pages supported by this device */
	vpd_buf = scsi_get_vpd_buf(sdev, 0);
	if (!vpd_buf)
		return;

	for (i = 4; i < vpd_buf->len; i++) {
		if (vpd_buf->data[i] == 0x80)
			scsi_update_vpd_page(sdev, 0x80, &sdev->vpd_pg80);
		if (vpd_buf->data[i] == 0x83)
			scsi_update_vpd_page(sdev, 0x83, &sdev->vpd_pg83);
	}
	kfree(vpd_buf);
}