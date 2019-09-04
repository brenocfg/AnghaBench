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
typedef  int /*<<< orphan*/  u8 ;
struct usb_ftdi {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ftdi_elan_edset_flush (struct usb_ftdi*,int /*<<< orphan*/ ,void*) ; 
 struct usb_ftdi* platform_device_to_usb_ftdi (struct platform_device*) ; 

int usb_ftdi_elan_edset_flush(struct platform_device *pdev, u8 ed_number,
			      void *endp)
{
	struct usb_ftdi *ftdi = platform_device_to_usb_ftdi(pdev);
	return ftdi_elan_edset_flush(ftdi, ed_number, endp);
}