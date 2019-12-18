#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ reg; } ;
struct TYPE_6__ {int /*<<< orphan*/  reg; } ;
struct TYPE_9__ {int /*<<< orphan*/  reg; } ;
struct TYPE_8__ {int /*<<< orphan*/  reg; } ;
struct TYPE_10__ {TYPE_2__ SYNCBUSY; TYPE_1__ CTRLA; TYPE_4__ INTFLAG; TYPE_3__ INTENCLR; } ;
struct usb_module {TYPE_5__ DEVICE; struct usb_module* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (struct usb_module*) ; 
 int /*<<< orphan*/  USB_CTRLA_ENABLE ; 
 int /*<<< orphan*/  USB_DEVICE_INTENCLR_MASK ; 
 int /*<<< orphan*/  USB_DEVICE_INTFLAG_MASK ; 
 scalar_t__ USB_SYNCBUSY_ENABLE ; 

void usb_disable(struct usb_module *module_inst) {
    Assert(module_inst);
    Assert(module_inst->hw);

    module_inst->hw->DEVICE.INTENCLR.reg = USB_DEVICE_INTENCLR_MASK;
    module_inst->hw->DEVICE.INTFLAG.reg  = USB_DEVICE_INTFLAG_MASK;
    module_inst->hw->DEVICE.CTRLA.reg &= ~USB_CTRLA_ENABLE;
    while (module_inst->hw->DEVICE.SYNCBUSY.reg == USB_SYNCBUSY_ENABLE)
        ;
}