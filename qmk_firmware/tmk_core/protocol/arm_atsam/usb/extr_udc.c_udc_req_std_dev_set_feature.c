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
struct TYPE_3__ {int wValue; int wIndex; scalar_t__ wLength; } ;
struct TYPE_4__ {int /*<<< orphan*/  callback; TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UDC_REMOTEWAKEUP_ENABLE () ; 
#define  USB_DEV_FEATURE_REMOTE_WAKEUP 134 
#define  USB_DEV_FEATURE_TEST_MODE 133 
 int /*<<< orphan*/  USB_DEV_STATUS_REMOTEWAKEUP ; 
#define  USB_DEV_TEST_MODE_FORCE_ENABLE 132 
#define  USB_DEV_TEST_MODE_J 131 
#define  USB_DEV_TEST_MODE_K 130 
#define  USB_DEV_TEST_MODE_PACKET 129 
#define  USB_DEV_TEST_MODE_SE0_NAK 128 
 int /*<<< orphan*/  udc_device_status ; 
 int /*<<< orphan*/  udc_reset () ; 
 TYPE_2__ udd_g_ctrlreq ; 
 int /*<<< orphan*/  udd_is_high_speed () ; 
 int /*<<< orphan*/  udd_test_mode_j ; 
 int /*<<< orphan*/  udd_test_mode_k ; 
 int /*<<< orphan*/  udd_test_mode_packet ; 
 int /*<<< orphan*/  udd_test_mode_se0_nak ; 

__attribute__((used)) static bool udc_req_std_dev_set_feature(void) {
    if (udd_g_ctrlreq.req.wLength) {
        return false;
    }

    switch (udd_g_ctrlreq.req.wValue) {
        case USB_DEV_FEATURE_REMOTE_WAKEUP:
#if (USB_CONFIG_ATTR_REMOTE_WAKEUP == (USB_DEVICE_ATTR & USB_CONFIG_ATTR_REMOTE_WAKEUP))
            udc_device_status |= CPU_TO_LE16(USB_DEV_STATUS_REMOTEWAKEUP);
            UDC_REMOTEWAKEUP_ENABLE();
            return true;
#else
            return false;
#endif

#ifdef USB_DEVICE_HS_SUPPORT
        case USB_DEV_FEATURE_TEST_MODE:
            if (!udd_is_high_speed()) {
                break;
            }
            if (udd_g_ctrlreq.req.wIndex & 0xff) {
                break;
            }
            // Unconfigure the device, terminating all ongoing requests
            udc_reset();
            switch ((udd_g_ctrlreq.req.wIndex >> 8) & 0xFF) {
                case USB_DEV_TEST_MODE_J:
                    udd_g_ctrlreq.callback = udd_test_mode_j;
                    return true;

                case USB_DEV_TEST_MODE_K:
                    udd_g_ctrlreq.callback = udd_test_mode_k;
                    return true;

                case USB_DEV_TEST_MODE_SE0_NAK:
                    udd_g_ctrlreq.callback = udd_test_mode_se0_nak;
                    return true;

                case USB_DEV_TEST_MODE_PACKET:
                    udd_g_ctrlreq.callback = udd_test_mode_packet;
                    return true;

                case USB_DEV_TEST_MODE_FORCE_ENABLE:  // Only for downstream facing hub ports
                default:
                    break;
            }
            break;
#endif
        default:
            break;
    }
    return false;
}