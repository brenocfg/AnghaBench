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
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {TYPE_1__* desc; } ;
struct TYPE_3__ {scalar_t__ bNumInterfaces; } ;

/* Variables and functions */
 int CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDC_REMOTEWAKEUP_DISABLE () ; 
 int /*<<< orphan*/  USB_DEV_STATUS_BUS_POWERED ; 
 int /*<<< orphan*/  USB_DEV_STATUS_REMOTEWAKEUP ; 
 int /*<<< orphan*/  USB_DEV_STATUS_SELF_POWERED ; 
 int udc_device_status ; 
 int /*<<< orphan*/  udc_iface_disable (scalar_t__) ; 
 scalar_t__ udc_num_configuration ; 
 TYPE_2__* udc_ptr_conf ; 

void udc_reset(void) {
    uint8_t iface_num;

    if (udc_num_configuration) {
        for (iface_num = 0; iface_num < udc_ptr_conf->desc->bNumInterfaces; iface_num++) {
            udc_iface_disable(iface_num);
        }
    }
    udc_num_configuration = 0;
#if (USB_CONFIG_ATTR_REMOTE_WAKEUP == (USB_DEVICE_ATTR & USB_CONFIG_ATTR_REMOTE_WAKEUP))
    if (CPU_TO_LE16(USB_DEV_STATUS_REMOTEWAKEUP) & udc_device_status) {
        // Remote wakeup is enabled then disable it
        UDC_REMOTEWAKEUP_DISABLE();
    }
#endif
    udc_device_status =
#if (USB_DEVICE_ATTR & USB_CONFIG_ATTR_SELF_POWERED)
        CPU_TO_LE16(USB_DEV_STATUS_SELF_POWERED);
#else
        CPU_TO_LE16(USB_DEV_STATUS_BUS_POWERED);
#endif
}