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
typedef  int uint8_t ;
struct usb_module {TYPE_3__* hw; } ;
struct TYPE_4__ {int reg; } ;
struct TYPE_5__ {TYPE_1__ DADD; } ;
struct TYPE_6__ {TYPE_2__ DEVICE; } ;

/* Variables and functions */
 int USB_DEVICE_DADD_ADDEN ; 

__attribute__((used)) static inline void usb_device_set_address(struct usb_module *module_inst, uint8_t address) { module_inst->hw->DEVICE.DADD.reg = USB_DEVICE_DADD_ADDEN | address; }