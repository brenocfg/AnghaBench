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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  reg; } ;
struct TYPE_4__ {TYPE_1__ FSMSTATUS; } ;
struct usb_module {TYPE_2__ DEVICE; struct usb_module* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (struct usb_module*) ; 

__attribute__((used)) static inline uint8_t usb_get_state_machine_status(struct usb_module *module_inst) {
    /* Sanity check arguments */
    Assert(module_inst);
    Assert(module_inst->hw);

    return module_inst->hw->DEVICE.FSMSTATUS.reg;
}