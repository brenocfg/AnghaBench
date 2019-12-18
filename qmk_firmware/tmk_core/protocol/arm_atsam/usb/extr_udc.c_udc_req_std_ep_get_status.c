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
typedef  int /*<<< orphan*/  udc_ep_status ;
typedef  int /*<<< orphan*/  le16_t ;
struct TYPE_3__ {int wLength; int wIndex; } ;
struct TYPE_4__ {TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_EP_STATUS_HALTED ; 
 scalar_t__ udd_ep_is_halted (int) ; 
 TYPE_2__ udd_g_ctrlreq ; 
 int /*<<< orphan*/  udd_set_setup_payload (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool udc_req_std_ep_get_status(void) {
    static le16_t udc_ep_status;

    if (udd_g_ctrlreq.req.wLength != sizeof(udc_ep_status)) {
        return false;
    }

    udc_ep_status = udd_ep_is_halted(udd_g_ctrlreq.req.wIndex & 0xFF) ? CPU_TO_LE16(USB_EP_STATUS_HALTED) : 0;

    udd_set_setup_payload((uint8_t *)&udc_ep_status, sizeof(udc_ep_status));
    return true;
}