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
typedef  int __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
#define  USB_REQ_CLEAR_FEATURE 140 
#define  USB_REQ_GET_CONFIGURATION 139 
#define  USB_REQ_GET_DESCRIPTOR 138 
#define  USB_REQ_GET_INTERFACE 137 
#define  USB_REQ_GET_STATUS 136 
#define  USB_REQ_SET_ADDRESS 135 
#define  USB_REQ_SET_CONFIGURATION 134 
#define  USB_REQ_SET_DESCRIPTOR 133 
#define  USB_REQ_SET_FEATURE 132 
#define  USB_REQ_SET_INTERFACE 131 
#define  USB_REQ_SET_ISOCH_DELAY 130 
#define  USB_REQ_SET_SEL 129 
#define  USB_REQ_SYNCH_FRAME 128 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_decode_get_configuration (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc3_decode_get_intf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc3_decode_get_set_descriptor (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc3_decode_get_status (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc3_decode_set_address (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc3_decode_set_clear_feature (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc3_decode_set_configuration (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc3_decode_set_intf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc3_decode_set_isoch_delay (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc3_decode_set_sel (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dwc3_decode_synch_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static inline const char *dwc3_decode_ctrl(char *str, __u8 bRequestType,
		__u8 bRequest, __u16 wValue, __u16 wIndex, __u16 wLength)
{
	switch (bRequest) {
	case USB_REQ_GET_STATUS:
		dwc3_decode_get_status(bRequestType, wIndex, wLength, str);
		break;
	case USB_REQ_CLEAR_FEATURE:
	case USB_REQ_SET_FEATURE:
		dwc3_decode_set_clear_feature(bRequestType, bRequest, wValue,
					      wIndex, str);
		break;
	case USB_REQ_SET_ADDRESS:
		dwc3_decode_set_address(wValue, str);
		break;
	case USB_REQ_GET_DESCRIPTOR:
	case USB_REQ_SET_DESCRIPTOR:
		dwc3_decode_get_set_descriptor(bRequestType, bRequest, wValue,
					       wIndex, wLength, str);
		break;
	case USB_REQ_GET_CONFIGURATION:
		dwc3_decode_get_configuration(wLength, str);
		break;
	case USB_REQ_SET_CONFIGURATION:
		dwc3_decode_set_configuration(wValue, str);
		break;
	case USB_REQ_GET_INTERFACE:
		dwc3_decode_get_intf(wIndex, wLength, str);
		break;
	case USB_REQ_SET_INTERFACE:
		dwc3_decode_set_intf(wValue, wIndex, str);
		break;
	case USB_REQ_SYNCH_FRAME:
		dwc3_decode_synch_frame(wIndex, wLength, str);
		break;
	case USB_REQ_SET_SEL:
		dwc3_decode_set_sel(wLength, str);
		break;
	case USB_REQ_SET_ISOCH_DELAY:
		dwc3_decode_set_isoch_delay(wValue, str);
		break;
	default:
		sprintf(str, "%02x %02x %02x %02x %02x %02x %02x %02x",
			bRequestType, bRequest,
			cpu_to_le16(wValue) & 0xff,
			cpu_to_le16(wValue) >> 8,
			cpu_to_le16(wIndex) & 0xff,
			cpu_to_le16(wIndex) >> 8,
			cpu_to_le16(wLength) & 0xff,
			cpu_to_le16(wLength) >> 8);
	}

	return str;
}