#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct usb_module {TYPE_6__* hw; } ;
struct TYPE_11__ {TYPE_4__* DeviceEndpoint; } ;
struct TYPE_12__ {TYPE_5__ DEVICE; } ;
struct TYPE_9__ {int /*<<< orphan*/  reg; } ;
struct TYPE_8__ {int reg; } ;
struct TYPE_7__ {int reg; } ;
struct TYPE_10__ {TYPE_3__ EPSTATUSCLR; TYPE_2__ EPINTFLAG; TYPE_1__ EPSTATUS; } ;

/* Variables and functions */
 int USB_DEVICE_EPINTFLAG_STALL0 ; 
 int USB_DEVICE_EPINTFLAG_STALL1 ; 
 int /*<<< orphan*/  USB_DEVICE_EPSTATUSCLR_STALLRQ0 ; 
 int /*<<< orphan*/  USB_DEVICE_EPSTATUSCLR_STALLRQ1 ; 
 int /*<<< orphan*/  USB_DEVICE_EPSTATUSSET_DTGLIN ; 
 int /*<<< orphan*/  USB_DEVICE_EPSTATUSSET_DTGLOUT ; 
 int USB_DEVICE_EPSTATUSSET_STALLRQ0 ; 
 int USB_DEVICE_EPSTATUSSET_STALLRQ1 ; 
 int USB_EP_ADDR_MASK ; 
 int USB_EP_DIR_IN ; 

void usb_device_endpoint_clear_halt(struct usb_module *module_inst, uint8_t ep) {
    uint8_t ep_num = ep & USB_EP_ADDR_MASK;

    if (ep & USB_EP_DIR_IN) {
        if (module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUS.reg & USB_DEVICE_EPSTATUSSET_STALLRQ1) {
            // Remove stall request
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_STALLRQ1;
            if (module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTFLAG.reg & USB_DEVICE_EPINTFLAG_STALL1) {
                module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_STALL1;
                // The Stall has occurred, then reset data toggle
                module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSSET_DTGLIN;
            }
        }
    } else {
        if (module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUS.reg & USB_DEVICE_EPSTATUSSET_STALLRQ0) {
            // Remove stall request
            module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_STALLRQ0;
            if (module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTFLAG.reg & USB_DEVICE_EPINTFLAG_STALL0) {
                module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_STALL0;
                // The Stall has occurred, then reset data toggle
                module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSSET_DTGLOUT;
            }
        }
    }
}