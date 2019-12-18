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

/* Variables and functions */
 int /*<<< orphan*/  UDD_EPCTRL_STALL_REQ ; 
 int /*<<< orphan*/  USB_EP_DIR_IN ; 
 int /*<<< orphan*/  USB_EP_DIR_OUT ; 
 int /*<<< orphan*/  udd_ep_control_state ; 
 int /*<<< orphan*/  usb_device ; 
 int /*<<< orphan*/  usb_device_endpoint_clear_halt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_device_endpoint_set_halt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udd_ctrl_stall_data(void) {
    udd_ep_control_state = UDD_EPCTRL_STALL_REQ;

    usb_device_endpoint_set_halt(&usb_device, USB_EP_DIR_IN);
    usb_device_endpoint_clear_halt(&usb_device, USB_EP_DIR_OUT);
}