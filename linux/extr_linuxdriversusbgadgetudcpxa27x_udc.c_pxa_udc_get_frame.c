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
struct usb_gadget {int dummy; } ;
struct pxa_udc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDCFNR ; 
 struct pxa_udc* to_gadget_udc (struct usb_gadget*) ; 
 int udc_readl (struct pxa_udc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxa_udc_get_frame(struct usb_gadget *_gadget)
{
	struct pxa_udc *udc = to_gadget_udc(_gadget);

	return (udc_readl(udc, UDCFNR) & 0x7ff);
}