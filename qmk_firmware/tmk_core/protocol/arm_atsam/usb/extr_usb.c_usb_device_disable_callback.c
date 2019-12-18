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
struct TYPE_3__ {int /*<<< orphan*/  reg; } ;
struct TYPE_4__ {TYPE_1__ INTENCLR; } ;
struct usb_module {TYPE_2__ DEVICE; struct usb_module* hw; int /*<<< orphan*/  device_enabled_callback_mask; } ;
typedef  enum usb_device_callback { ____Placeholder_usb_device_callback } usb_device_callback ;
typedef  enum status_code { ____Placeholder_status_code } status_code ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (struct usb_module*) ; 
 int STATUS_OK ; 
 int /*<<< orphan*/ * _usb_device_irq_bits ; 

enum status_code usb_device_disable_callback(struct usb_module *module_inst, enum usb_device_callback callback_type) {
    /* Sanity check arguments */
    Assert(module_inst);
    Assert(module_inst->hw);

    /* Disable callback */
    module_inst->device_enabled_callback_mask &= ~_usb_device_irq_bits[callback_type];

    module_inst->hw->DEVICE.INTENCLR.reg = _usb_device_irq_bits[callback_type];

    return STATUS_OK;
}