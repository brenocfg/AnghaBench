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
struct TYPE_2__ {int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDD_EPCTRL_HANDSHAKE_WAIT_IN_ZLP ; 
 int /*<<< orphan*/  udd_ctrl_buffer ; 
 int /*<<< orphan*/  udd_ep_control_state ; 
 TYPE_1__ udd_g_ctrlreq ; 
 int /*<<< orphan*/  usb_device ; 
 int /*<<< orphan*/  usb_device_endpoint_setup_buffer_job (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_device_endpoint_write_buffer_job (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udd_ctrl_send_zlp_in(void) {
    udd_ep_control_state = UDD_EPCTRL_HANDSHAKE_WAIT_IN_ZLP;
    usb_device_endpoint_setup_buffer_job(&usb_device, udd_ctrl_buffer);
    usb_device_endpoint_write_buffer_job(&usb_device, 0, udd_g_ctrlreq.payload, 0);
}