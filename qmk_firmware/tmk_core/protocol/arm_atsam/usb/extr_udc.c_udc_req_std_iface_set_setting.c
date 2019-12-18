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
typedef  int uint8_t ;
struct TYPE_3__ {int wIndex; int wValue; scalar_t__ wLength; } ;
struct TYPE_4__ {TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  udc_iface_disable (int) ; 
 int udc_iface_enable (int,int) ; 
 int /*<<< orphan*/  udc_num_configuration ; 
 TYPE_2__ udd_g_ctrlreq ; 

__attribute__((used)) static bool udc_req_std_iface_set_setting(void) {
    uint8_t iface_num, setting_num;

    if (udd_g_ctrlreq.req.wLength) {
        return false;  // Error in request
    }
    if (!udc_num_configuration) {
        return false;  // The device is not is configured state yet
    }

    iface_num   = udd_g_ctrlreq.req.wIndex & 0xFF;
    setting_num = udd_g_ctrlreq.req.wValue & 0xFF;

    // Disable current setting
    if (!udc_iface_disable(iface_num)) {
        return false;
    }

    // Enable new setting
    return udc_iface_enable(iface_num, setting_num);
}