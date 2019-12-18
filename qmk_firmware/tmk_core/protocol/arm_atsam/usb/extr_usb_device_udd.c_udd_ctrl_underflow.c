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
struct usb_endpoint_callback_parameter {int /*<<< orphan*/  endpoint_address; } ;

/* Variables and functions */
 scalar_t__ UDD_EPCTRL_DATA_OUT ; 
 scalar_t__ UDD_EPCTRL_HANDSHAKE_WAIT_OUT_ZLP ; 
 int /*<<< orphan*/  udd_ctrl_send_zlp_in () ; 
 scalar_t__ udd_ep_control_state ; 
 int /*<<< orphan*/  usb_device ; 
 int /*<<< orphan*/  usb_device_endpoint_set_halt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udd_ctrl_underflow(void *pointer) {
    struct usb_endpoint_callback_parameter *ep_callback_para = (struct usb_endpoint_callback_parameter *)pointer;

    if (UDD_EPCTRL_DATA_OUT == udd_ep_control_state) {
        /* Host want to stop OUT transaction
         * then stop to wait OUT data phase and wait IN ZLP handshake */
        udd_ctrl_send_zlp_in();
    } else if (UDD_EPCTRL_HANDSHAKE_WAIT_OUT_ZLP == udd_ep_control_state) {
        /* A OUT handshake is waiting by device,
         * but host want extra IN data then stall extra IN data */
        usb_device_endpoint_set_halt(&usb_device, ep_callback_para->endpoint_address);
    }
}