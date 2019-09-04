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
 int USBAT_FLASH_MEDIA_CF ; 
 int USBAT_FLASH_MEDIA_NONE ; 
 unsigned char USBAT_UIO_UI0 ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*) ; 

__attribute__((used)) static int usbat_flash_check_media_present(struct us_data *us,
					   unsigned char *uio)
{
	if (*uio & USBAT_UIO_UI0) {
		usb_stor_dbg(us, "no media detected\n");
		return USBAT_FLASH_MEDIA_NONE;
	}

	return USBAT_FLASH_MEDIA_CF;
}