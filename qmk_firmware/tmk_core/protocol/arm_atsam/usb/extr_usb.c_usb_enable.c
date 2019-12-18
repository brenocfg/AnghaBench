#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ reg; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg; } ;
struct TYPE_6__ {TYPE_2__ SYNCBUSY; TYPE_1__ CTRLA; } ;
struct usb_module {TYPE_3__ DEVICE; struct usb_module* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (struct usb_module*) ; 
 int /*<<< orphan*/  USB_CTRLA_ENABLE ; 
 scalar_t__ USB_SYNCBUSY_ENABLE ; 

void usb_enable(struct usb_module *module_inst) {
    Assert(module_inst);
    Assert(module_inst->hw);

    module_inst->hw->DEVICE.CTRLA.reg |= USB_CTRLA_ENABLE;
    while (module_inst->hw->DEVICE.SYNCBUSY.reg == USB_SYNCBUSY_ENABLE)
        ;
}