#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct TYPE_2__ {struct mts_desc* scsi_status; } ;
struct mts_desc {TYPE_1__ context; int /*<<< orphan*/  urb; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mts_desc*) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct mts_desc* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mts_usb_disconnect (struct usb_interface *intf)
{
	struct mts_desc *desc = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);

	usb_kill_urb(desc->urb);
	scsi_remove_host(desc->host);

	scsi_host_put(desc->host);
	usb_free_urb(desc->urb);
	kfree(desc->context.scsi_status);
	kfree(desc);
}