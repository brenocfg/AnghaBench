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
 int USBAT_UIO_1 ; 
 int USBAT_UIO_ACKD ; 
 int USBAT_UIO_EPAD ; 
 int USBAT_UIO_OE0 ; 
 int USBAT_UIO_OE1 ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int USB_STOR_XFER_GOOD ; 
 int usbat_write_user_io (struct us_data*,int,int) ; 

__attribute__((used)) static int usbat_device_enable_cdt(struct us_data *us)
{
	int rc;

	/* Enable peripheral control signals and card detect */
	rc = usbat_write_user_io(us,
							 USBAT_UIO_ACKD | USBAT_UIO_OE1  | USBAT_UIO_OE0,
							 USBAT_UIO_EPAD | USBAT_UIO_1);
	if (rc != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	return USB_STOR_TRANSPORT_GOOD;
}