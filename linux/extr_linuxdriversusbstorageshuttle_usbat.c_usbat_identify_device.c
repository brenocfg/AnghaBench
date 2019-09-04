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
struct usbat_info {int /*<<< orphan*/  devicetype; } ;
struct us_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBAT_ATA ; 
 int /*<<< orphan*/  USBAT_ATA_CMD ; 
 int /*<<< orphan*/  USBAT_DEV_FLASH ; 
 int /*<<< orphan*/  USBAT_DEV_HP8200 ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int USB_STOR_XFER_GOOD ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*) ; 
 int usbat_device_reset (struct us_data*) ; 
 int usbat_get_status (struct us_data*,unsigned char*) ; 
 int usbat_write (struct us_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int usbat_identify_device(struct us_data *us,
				 struct usbat_info *info)
{
	int rc;
	unsigned char status;

	if (!us || !info)
		return USB_STOR_TRANSPORT_ERROR;

	rc = usbat_device_reset(us);
	if (rc != USB_STOR_TRANSPORT_GOOD)
		return rc;
	msleep(500);

	/*
	 * In attempt to distinguish between HP CDRW's and Flash readers, we now
	 * execute the IDENTIFY PACKET DEVICE command. On ATA devices (i.e. flash
	 * readers), this command should fail with error. On ATAPI devices (i.e.
	 * CDROM drives), it should succeed.
	 */
	rc = usbat_write(us, USBAT_ATA, USBAT_ATA_CMD, 0xA1);
 	if (rc != USB_STOR_XFER_GOOD)
 		return USB_STOR_TRANSPORT_ERROR;

	rc = usbat_get_status(us, &status);
 	if (rc != USB_STOR_XFER_GOOD)
 		return USB_STOR_TRANSPORT_ERROR;

	/* Check for error bit, or if the command 'fell through' */
	if (status == 0xA1 || !(status & 0x01)) {
		/* Device is HP 8200 */
		usb_stor_dbg(us, "Detected HP8200 CDRW\n");
		info->devicetype = USBAT_DEV_HP8200;
	} else {
		/* Device is a CompactFlash reader/writer */
		usb_stor_dbg(us, "Detected Flash reader/writer\n");
		info->devicetype = USBAT_DEV_FLASH;
	}

	return USB_STOR_TRANSPORT_GOOD;
}