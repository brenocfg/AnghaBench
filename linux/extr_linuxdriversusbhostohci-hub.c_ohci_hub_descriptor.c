#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int* DeviceRemovable; } ;
struct TYPE_4__ {TYPE_1__ hs; } ;
struct usb_hub_descriptor {int bPwrOn2PwrGood; int bNbrPorts; int bDescLength; TYPE_2__ u; int /*<<< orphan*/  wHubCharacteristics; scalar_t__ bHubContrCurrent; int /*<<< orphan*/  bDescriptorType; } ;
struct ohci_hcd {int num_ports; } ;

/* Variables and functions */
 int HUB_CHAR_COMMON_LPSM ; 
 int HUB_CHAR_COMMON_OCPM ; 
 int HUB_CHAR_INDV_PORT_LPSM ; 
 int HUB_CHAR_INDV_PORT_OCPM ; 
 int HUB_CHAR_NO_LPSM ; 
 int HUB_CHAR_NO_OCPM ; 
 int RH_A_NOCP ; 
 int RH_A_NPS ; 
 int RH_A_OCPM ; 
 int RH_A_POTPGT ; 
 int RH_A_PSM ; 
 int RH_B_DR ; 
 int /*<<< orphan*/  USB_DT_HUB ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int roothub_a (struct ohci_hcd*) ; 
 int roothub_b (struct ohci_hcd*) ; 

__attribute__((used)) static void
ohci_hub_descriptor (
	struct ohci_hcd			*ohci,
	struct usb_hub_descriptor	*desc
) {
	u32		rh = roothub_a (ohci);
	u16		temp;

	desc->bDescriptorType = USB_DT_HUB;
	desc->bPwrOn2PwrGood = (rh & RH_A_POTPGT) >> 24;
	desc->bHubContrCurrent = 0;

	desc->bNbrPorts = ohci->num_ports;
	temp = 1 + (ohci->num_ports / 8);
	desc->bDescLength = 7 + 2 * temp;

	temp = HUB_CHAR_COMMON_LPSM | HUB_CHAR_COMMON_OCPM;
	if (rh & RH_A_NPS)		/* no power switching? */
		temp |= HUB_CHAR_NO_LPSM;
	if (rh & RH_A_PSM)		/* per-port power switching? */
		temp |= HUB_CHAR_INDV_PORT_LPSM;
	if (rh & RH_A_NOCP)		/* no overcurrent reporting? */
		temp |= HUB_CHAR_NO_OCPM;
	else if (rh & RH_A_OCPM)	/* per-port overcurrent reporting? */
		temp |= HUB_CHAR_INDV_PORT_OCPM;
	desc->wHubCharacteristics = cpu_to_le16(temp);

	/* ports removable, and usb 1.0 legacy PortPwrCtrlMask */
	rh = roothub_b (ohci);
	memset(desc->u.hs.DeviceRemovable, 0xff,
			sizeof(desc->u.hs.DeviceRemovable));
	desc->u.hs.DeviceRemovable[0] = rh & RH_B_DR;
	if (ohci->num_ports > 7) {
		desc->u.hs.DeviceRemovable[1] = (rh & RH_B_DR) >> 8;
		desc->u.hs.DeviceRemovable[2] = 0xff;
	} else
		desc->u.hs.DeviceRemovable[1] = 0xff;
}