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
struct usb_module {TYPE_5__* hw; } ;
struct TYPE_12__ {int /*<<< orphan*/  reg; } ;
struct TYPE_10__ {TYPE_3__* DeviceEndpoint; } ;
struct TYPE_11__ {TYPE_4__ DEVICE; } ;
struct TYPE_8__ {int /*<<< orphan*/  reg; } ;
struct TYPE_7__ {int /*<<< orphan*/  reg; } ;
struct TYPE_9__ {TYPE_2__ EPINTFLAG; TYPE_1__ EPSTATUSSET; TYPE_6__ EPSTATUSCLR; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_DEVICE_EPINTFLAG_TRCPT0 ; 
 int /*<<< orphan*/  USB_DEVICE_EPINTFLAG_TRCPT1 ; 
 int /*<<< orphan*/  USB_DEVICE_EPSTATUSCLR_BK1RDY ; 
 int /*<<< orphan*/  USB_DEVICE_EPSTATUSSET_BK0RDY ; 
 int USB_EP_ADDR_MASK ; 
 int USB_EP_DIR_IN ; 

void usb_device_endpoint_abort_job(struct usb_module *module_inst, uint8_t ep) {
    uint8_t ep_num;
    ep_num = ep & USB_EP_ADDR_MASK;

    // Stop transfer
    if (ep & USB_EP_DIR_IN) {
        module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSCLR.reg = USB_DEVICE_EPSTATUSCLR_BK1RDY;
        // Eventually ack a transfer occur during abort
        module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT1;
    } else {
        module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPSTATUSSET.reg = USB_DEVICE_EPSTATUSSET_BK0RDY;
        // Eventually ack a transfer occur during abort
        module_inst->hw->DEVICE.DeviceEndpoint[ep_num].EPINTFLAG.reg = USB_DEVICE_EPINTFLAG_TRCPT0;
    }
}