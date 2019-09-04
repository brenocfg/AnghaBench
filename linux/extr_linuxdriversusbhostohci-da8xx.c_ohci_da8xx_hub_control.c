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
typedef  int u16 ;
struct TYPE_2__ {struct device* controller; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
#define  ClearPortFeature 132 
 int EPIPE ; 
#define  GetPortStatus 131 
 int RH_PS_OCIC ; 
 int RH_PS_POCI ; 
 int RH_PS_PPS ; 
#define  SetPortFeature 130 
#define  USB_PORT_FEAT_C_OVER_CURRENT 129 
#define  USB_PORT_FEAT_POWER 128 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  hcd_to_ohci (struct usb_hcd*) ; 
 int ocic_mask ; 
 int /*<<< orphan*/  ohci_da8xx_get_oci (struct usb_hcd*) ; 
 int /*<<< orphan*/  ohci_da8xx_get_power (struct usb_hcd*) ; 
 int /*<<< orphan*/  ohci_da8xx_set_power (struct usb_hcd*,int) ; 
 int orig_ohci_hub_control (struct usb_hcd*,int,int,int,char*,int) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int roothub_portstatus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ohci_da8xx_hub_control(struct usb_hcd *hcd, u16 typeReq, u16 wValue,
				  u16 wIndex, char *buf, u16 wLength)
{
	struct device *dev		= hcd->self.controller;
	int temp;

	switch (typeReq) {
	case GetPortStatus:
		/* Check the port number */
		if (wIndex != 1)
			break;

		dev_dbg(dev, "GetPortStatus(%u)\n", wIndex);

		temp = roothub_portstatus(hcd_to_ohci(hcd), wIndex - 1);

		/* The port power status (PPS) bit defaults to 1 */
		if (!ohci_da8xx_get_power(hcd))
			temp &= ~RH_PS_PPS;

		/* The port over-current indicator (POCI) bit is always 0 */
		if (ohci_da8xx_get_oci(hcd) > 0)
			temp |=  RH_PS_POCI;

		/* The over-current indicator change (OCIC) bit is 0 too */
		if (ocic_mask & (1 << wIndex))
			temp |=  RH_PS_OCIC;

		put_unaligned(cpu_to_le32(temp), (__le32 *)buf);
		return 0;
	case SetPortFeature:
		temp = 1;
		goto check_port;
	case ClearPortFeature:
		temp = 0;

check_port:
		/* Check the port number */
		if (wIndex != 1)
			break;

		switch (wValue) {
		case USB_PORT_FEAT_POWER:
			dev_dbg(dev, "%sPortFeature(%u): %s\n",
				temp ? "Set" : "Clear", wIndex, "POWER");

			return ohci_da8xx_set_power(hcd, temp) ? -EPIPE : 0;
		case USB_PORT_FEAT_C_OVER_CURRENT:
			dev_dbg(dev, "%sPortFeature(%u): %s\n",
				temp ? "Set" : "Clear", wIndex,
				"C_OVER_CURRENT");

			if (temp)
				ocic_mask |= 1 << wIndex;
			else
				ocic_mask &= ~(1 << wIndex);
			return 0;
		}
	}

	return orig_ohci_hub_control(hcd, typeReq, wValue,
			wIndex, buf, wLength);
}