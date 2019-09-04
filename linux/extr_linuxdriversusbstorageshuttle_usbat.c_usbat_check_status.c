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
 int USB_STOR_TRANSPORT_FAILED ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int USB_STOR_XFER_GOOD ; 
 int usbat_get_status (struct us_data*,unsigned char*) ; 

__attribute__((used)) static int usbat_check_status(struct us_data *us)
{
	unsigned char *reply = us->iobuf;
	int rc;

	rc = usbat_get_status(us, reply);
	if (rc != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_FAILED;

	/* error/check condition (0x51 is ok) */
	if (*reply & 0x01 && *reply != 0x51)
		return USB_STOR_TRANSPORT_FAILED;

	/* device fault */
	if (*reply & 0x20)
		return USB_STOR_TRANSPORT_FAILED;

	return USB_STOR_TRANSPORT_GOOD;
}