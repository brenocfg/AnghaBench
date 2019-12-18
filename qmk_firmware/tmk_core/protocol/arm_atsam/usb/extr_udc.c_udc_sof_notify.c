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
typedef  size_t uint8_t ;
struct TYPE_6__ {TYPE_2__** udi_apis; TYPE_1__* desc; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* sof_notify ) () ;} ;
struct TYPE_4__ {size_t bNumInterfaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ udc_num_configuration ; 
 TYPE_3__* udc_ptr_conf ; 

void udc_sof_notify(void) {
    uint8_t iface_num;

    if (udc_num_configuration) {
        for (iface_num = 0; iface_num < udc_ptr_conf->desc->bNumInterfaces; iface_num++) {
            if (udc_ptr_conf->udi_apis[iface_num]->sof_notify != NULL) {
                udc_ptr_conf->udi_apis[iface_num]->sof_notify();
            }
        }
    }
}