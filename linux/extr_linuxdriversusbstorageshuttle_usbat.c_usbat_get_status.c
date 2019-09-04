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
struct us_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBAT_ATA ; 
 int /*<<< orphan*/  USBAT_ATA_STATUS ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,unsigned char) ; 
 int usbat_read (struct us_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int usbat_get_status(struct us_data *us, unsigned char *status)
{
	int rc;
	rc = usbat_read(us, USBAT_ATA, USBAT_ATA_STATUS, status);

	usb_stor_dbg(us, "0x%02X\n", *status);
	return rc;
}