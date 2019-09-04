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
typedef  int /*<<< orphan*/  u32 ;
struct usb_endpoint_descriptor {int dummy; } ;
struct renesas_usb3_ep {scalar_t__ dir_in; } ;
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PN_MOD_DIR ; 
 int /*<<< orphan*/  PN_MOD_EPNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PN_MOD_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB3_PN_MOD ; 
 struct renesas_usb3* usb3_ep_to_usb3 (struct renesas_usb3_ep*) ; 
 int /*<<< orphan*/  usb3_write (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_endpoint_num (struct usb_endpoint_descriptor const*) ; 
 int /*<<< orphan*/  usb_endpoint_type (struct usb_endpoint_descriptor const*) ; 

__attribute__((used)) static void usb3_write_pn_mod(struct renesas_usb3_ep *usb3_ep,
			      const struct usb_endpoint_descriptor *desc)
{
	struct renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	u32 val = 0;

	val |= usb3_ep->dir_in ? PN_MOD_DIR : 0;
	val |= PN_MOD_TYPE(usb_endpoint_type(desc));
	val |= PN_MOD_EPNUM(usb_endpoint_num(desc));
	usb3_write(usb3, val, USB3_PN_MOD);
}