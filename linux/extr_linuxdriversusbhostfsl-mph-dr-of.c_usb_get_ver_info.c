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
struct device_node {int dummy; } ;
typedef  enum fsl_usb2_controller_ver { ____Placeholder_fsl_usb2_controller_ver } fsl_usb2_controller_ver ;

/* Variables and functions */
 int FSL_USB_VER_1_6 ; 
 int FSL_USB_VER_2_2 ; 
 int FSL_USB_VER_2_4 ; 
 int FSL_USB_VER_2_5 ; 
 int FSL_USB_VER_NONE ; 
 int FSL_USB_VER_OLD ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 

__attribute__((used)) static enum fsl_usb2_controller_ver usb_get_ver_info(struct device_node *np)
{
	enum fsl_usb2_controller_ver ver = FSL_USB_VER_NONE;

	/*
	 * returns 1 for usb controller version 1.6
	 * returns 2 for usb controller version 2.2
	 * returns 3 for usb controller version 2.4
	 * returns 4 for usb controller version 2.5
	 * returns 0 otherwise
	 */
	if (of_device_is_compatible(np, "fsl-usb2-dr")) {
		if (of_device_is_compatible(np, "fsl-usb2-dr-v1.6"))
			ver = FSL_USB_VER_1_6;
		else if (of_device_is_compatible(np, "fsl-usb2-dr-v2.2"))
			ver = FSL_USB_VER_2_2;
		else if (of_device_is_compatible(np, "fsl-usb2-dr-v2.4"))
			ver = FSL_USB_VER_2_4;
		else if (of_device_is_compatible(np, "fsl-usb2-dr-v2.5"))
			ver = FSL_USB_VER_2_5;
		else /* for previous controller versions */
			ver = FSL_USB_VER_OLD;

		if (ver > FSL_USB_VER_NONE)
			return ver;
	}

	if (of_device_is_compatible(np, "fsl,mpc5121-usb2-dr"))
		return FSL_USB_VER_OLD;

	if (of_device_is_compatible(np, "fsl-usb2-mph")) {
		if (of_device_is_compatible(np, "fsl-usb2-mph-v1.6"))
			ver = FSL_USB_VER_1_6;
		else if (of_device_is_compatible(np, "fsl-usb2-mph-v2.2"))
			ver = FSL_USB_VER_2_2;
		else if (of_device_is_compatible(np, "fsl-usb2-mph-v2.4"))
			ver = FSL_USB_VER_2_4;
		else if (of_device_is_compatible(np, "fsl-usb2-mph-v2.5"))
			ver = FSL_USB_VER_2_5;
		else /* for previous controller versions */
			ver = FSL_USB_VER_OLD;
	}

	return ver;
}