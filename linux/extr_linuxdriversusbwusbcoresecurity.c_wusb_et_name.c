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
typedef  int u8 ;

/* Variables and functions */
#define  USB_ENC_TYPE_CCM_1 131 
#define  USB_ENC_TYPE_RSA_1 130 
#define  USB_ENC_TYPE_UNSECURE 129 
#define  USB_ENC_TYPE_WIRED 128 

const char *wusb_et_name(u8 x)
{
	switch (x) {
	case USB_ENC_TYPE_UNSECURE:	return "unsecure";
	case USB_ENC_TYPE_WIRED:	return "wired";
	case USB_ENC_TYPE_CCM_1:	return "CCM-1";
	case USB_ENC_TYPE_RSA_1:	return "RSA-1";
	default:			return "unknown";
	}
}