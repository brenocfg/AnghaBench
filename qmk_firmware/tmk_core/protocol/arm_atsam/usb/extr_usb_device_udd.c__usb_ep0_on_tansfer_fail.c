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
struct usb_module {int dummy; } ;
struct usb_endpoint_callback_parameter {int endpoint_address; } ;

/* Variables and functions */
 int USB_EP_DIR_IN ; 
 int /*<<< orphan*/  udd_ctrl_overflow (void*) ; 
 int /*<<< orphan*/  udd_ctrl_underflow (void*) ; 

__attribute__((used)) static void _usb_ep0_on_tansfer_fail(struct usb_module *module_inst, void *pointer) {
    struct usb_endpoint_callback_parameter *ep_callback_para = (struct usb_endpoint_callback_parameter *)pointer;

    if (ep_callback_para->endpoint_address & USB_EP_DIR_IN) {
        udd_ctrl_underflow(pointer);
    } else {
        udd_ctrl_overflow(pointer);
    }
}