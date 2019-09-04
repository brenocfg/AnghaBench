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
struct usb_hub_descriptor {int bDescLength; int bNbrPorts; int /*<<< orphan*/  wHubCharacteristics; int /*<<< orphan*/  bDescriptorType; } ;

/* Variables and functions */
 int HUB_CHAR_COMMON_OCPM ; 
 int HUB_CHAR_INDV_PORT_LPSM ; 
 int /*<<< orphan*/  USB_DT_HUB ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (struct usb_hub_descriptor*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
hub_descriptor(struct usb_hub_descriptor *desc)
{
	memset(desc, 0, sizeof(*desc));
	/*
	 * See Table 11-13: Hub Descriptor in USB 2.0 spec.
	 */
	desc->bDescriptorType = USB_DT_HUB; /* hub descriptor */
	desc->bDescLength = 9;
	desc->wHubCharacteristics = cpu_to_le16(HUB_CHAR_INDV_PORT_LPSM |
						HUB_CHAR_COMMON_OCPM);
	desc->bNbrPorts = 1;
}