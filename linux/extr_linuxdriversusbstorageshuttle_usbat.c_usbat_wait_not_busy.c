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
struct us_data {unsigned char* iobuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBAT_ATA ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_FAILED ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int USB_STOR_XFER_GOOD ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,int) ; 
 int usbat_get_status (struct us_data*,unsigned char*) ; 
 int usbat_read (struct us_data*,int /*<<< orphan*/ ,int,unsigned char*) ; 

__attribute__((used)) static int usbat_wait_not_busy(struct us_data *us, int minutes)
{
	int i;
	int result;
	unsigned char *status = us->iobuf;

	/*
	 * Synchronizing cache on a CDR could take a heck of a long time,
	 * but probably not more than 10 minutes or so. On the other hand,
	 * doing a full blank on a CDRW at speed 1 will take about 75
	 * minutes!
	 */

	for (i=0; i<1200+minutes*60; i++) {

 		result = usbat_get_status(us, status);

		if (result!=USB_STOR_XFER_GOOD)
			return USB_STOR_TRANSPORT_ERROR;
		if (*status & 0x01) { /* check condition */
			result = usbat_read(us, USBAT_ATA, 0x10, status);
			return USB_STOR_TRANSPORT_FAILED;
		}
		if (*status & 0x20) /* device fault */
			return USB_STOR_TRANSPORT_FAILED;

		if ((*status & 0x80)==0x00) { /* not busy */
			usb_stor_dbg(us, "Waited not busy for %d steps\n", i);
			return USB_STOR_TRANSPORT_GOOD;
		}

		if (i<500)
			msleep(10); /* 5 seconds */
		else if (i<700)
			msleep(50); /* 10 seconds */
		else if (i<1200)
			msleep(100); /* 50 seconds */
		else
			msleep(1000); /* X minutes */
	}

	usb_stor_dbg(us, "Waited not busy for %d minutes, timing out\n",
		     minutes);
	return USB_STOR_TRANSPORT_FAILED;
}