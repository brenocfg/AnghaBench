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
struct us_data {int protocol; char* transport_name; int max_lun; void* transport_reset; void* transport; } ;

/* Variables and functions */
#define  USB_PR_BULK 130 
#define  USB_PR_CB 129 
#define  USB_PR_CBI 128 
 void* usb_stor_Bulk_reset ; 
 void* usb_stor_Bulk_transport ; 
 void* usb_stor_CB_reset ; 
 void* usb_stor_CB_transport ; 

__attribute__((used)) static void get_transport(struct us_data *us)
{
	switch (us->protocol) {
	case USB_PR_CB:
		us->transport_name = "Control/Bulk";
		us->transport = usb_stor_CB_transport;
		us->transport_reset = usb_stor_CB_reset;
		us->max_lun = 7;
		break;

	case USB_PR_CBI:
		us->transport_name = "Control/Bulk/Interrupt";
		us->transport = usb_stor_CB_transport;
		us->transport_reset = usb_stor_CB_reset;
		us->max_lun = 7;
		break;

	case USB_PR_BULK:
		us->transport_name = "Bulk";
		us->transport = usb_stor_Bulk_transport;
		us->transport_reset = usb_stor_Bulk_reset;
		break;
	}
}