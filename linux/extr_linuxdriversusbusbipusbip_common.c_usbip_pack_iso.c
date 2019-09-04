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
struct usbip_iso_packet_descriptor {int /*<<< orphan*/  actual_length; int /*<<< orphan*/  status; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct usb_iso_packet_descriptor {int /*<<< orphan*/  actual_length; int /*<<< orphan*/  status; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;

/* Variables and functions */

__attribute__((used)) static void usbip_pack_iso(struct usbip_iso_packet_descriptor *iso,
			   struct usb_iso_packet_descriptor *uiso, int pack)
{
	if (pack) {
		iso->offset		= uiso->offset;
		iso->length		= uiso->length;
		iso->status		= uiso->status;
		iso->actual_length	= uiso->actual_length;
	} else {
		uiso->offset		= iso->offset;
		uiso->length		= iso->length;
		uiso->status		= iso->status;
		uiso->actual_length	= iso->actual_length;
	}
}