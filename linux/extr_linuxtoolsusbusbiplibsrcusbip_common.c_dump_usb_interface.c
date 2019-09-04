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
struct usbip_usb_interface {int /*<<< orphan*/  bInterfaceProtocol; int /*<<< orphan*/  bInterfaceSubClass; int /*<<< orphan*/  bInterfaceClass; } ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,char*,char*) ; 
 int /*<<< orphan*/  usbip_names_get_class (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dump_usb_interface(struct usbip_usb_interface *uinf)
{
	char buff[100];

	usbip_names_get_class(buff, sizeof(buff),
			uinf->bInterfaceClass,
			uinf->bInterfaceSubClass,
			uinf->bInterfaceProtocol);
	dbg("%-20s = %s", "Interface(C/SC/P)", buff);
}