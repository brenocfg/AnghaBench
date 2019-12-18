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
struct TYPE_3__ {scalar_t__ wLength; } ;
struct TYPE_4__ {int /*<<< orphan*/  callback; TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  udc_valid_address ; 
 TYPE_2__ udd_g_ctrlreq ; 

__attribute__((used)) static bool udc_req_std_dev_set_address(void) {
    if (udd_g_ctrlreq.req.wLength) {
        return false;
    }

    // The address must be changed at the end of setup request after the handshake
    // then we use a callback to change address
    udd_g_ctrlreq.callback = udc_valid_address;
    return true;
}