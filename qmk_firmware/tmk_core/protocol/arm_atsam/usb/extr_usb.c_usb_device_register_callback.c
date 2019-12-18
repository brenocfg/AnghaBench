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
typedef  struct usb_module* usb_device_callback_t ;
struct usb_module {int /*<<< orphan*/  device_registered_callback_mask; struct usb_module** device_callback; } ;
typedef  enum usb_device_callback { ____Placeholder_usb_device_callback } usb_device_callback ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (struct usb_module*) ; 
 int STATUS_OK ; 
 int /*<<< orphan*/ * _usb_device_irq_bits ; 

enum status_code usb_device_register_callback(struct usb_module *module_inst, enum usb_device_callback callback_type, usb_device_callback_t callback_func) {
    /* Sanity check arguments */
    Assert(module_inst);
    Assert(callback_func);

    /* Register callback function */
    module_inst->device_callback[callback_type] = callback_func;

    /* Set the bit corresponding to the callback_type */
    module_inst->device_registered_callback_mask |= _usb_device_irq_bits[callback_type];

    return STATUS_OK;
}