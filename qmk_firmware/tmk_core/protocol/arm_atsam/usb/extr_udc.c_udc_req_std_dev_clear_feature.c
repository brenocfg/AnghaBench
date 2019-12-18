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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ wValue; scalar_t__ wLength; } ;
struct TYPE_4__ {TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDC_REMOTEWAKEUP_DISABLE () ; 
 scalar_t__ USB_DEV_FEATURE_REMOTE_WAKEUP ; 
 scalar_t__ USB_DEV_STATUS_REMOTEWAKEUP ; 
 int /*<<< orphan*/  udc_device_status ; 
 TYPE_2__ udd_g_ctrlreq ; 

__attribute__((used)) static bool udc_req_std_dev_clear_feature(void) {
    if (udd_g_ctrlreq.req.wLength) {
        return false;
    }

    if (udd_g_ctrlreq.req.wValue == USB_DEV_FEATURE_REMOTE_WAKEUP) {
        udc_device_status &= CPU_TO_LE16(~(uint32_t)USB_DEV_STATUS_REMOTEWAKEUP);
#if (USB_CONFIG_ATTR_REMOTE_WAKEUP == (USB_DEVICE_ATTR & USB_CONFIG_ATTR_REMOTE_WAKEUP))
        UDC_REMOTEWAKEUP_DISABLE();
#endif
        return true;
    }
    return false;
}