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
struct usbnet {int dummy; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 scalar_t__ CDC_NCM_COMM_ALTSETTING_NCM ; 
 int /*<<< orphan*/  CDC_NCM_DATA_ALTSETTING_NCM ; 
 int ENODEV ; 
 int cdc_ncm_bind_common (struct usbnet*,struct usb_interface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cdc_ncm_select_altsetting (struct usb_interface*) ; 

__attribute__((used)) static int cdc_ncm_bind(struct usbnet *dev, struct usb_interface *intf)
{
	/* MBIM backwards compatible function? */
	if (cdc_ncm_select_altsetting(intf) != CDC_NCM_COMM_ALTSETTING_NCM)
		return -ENODEV;

	/* The NCM data altsetting is fixed, so we hard-coded it.
	 * Additionally, generic NCM devices are assumed to accept arbitrarily
	 * placed NDP.
	 */
	return cdc_ncm_bind_common(dev, intf, CDC_NCM_DATA_ALTSETTING_NCM, 0);
}