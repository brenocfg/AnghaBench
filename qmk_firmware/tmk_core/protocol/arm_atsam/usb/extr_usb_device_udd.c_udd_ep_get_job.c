#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  udd_ep_job_t ;
typedef  int udd_ep_id_t ;

/* Variables and functions */
 int USB_EP_ADDR_MASK ; 
 int USB_EP_DIR_IN ; 
 int /*<<< orphan*/ * udd_ep_job ; 

__attribute__((used)) static udd_ep_job_t *udd_ep_get_job(udd_ep_id_t ep) {
    if ((ep == 0) || (ep == 0x80)) {
        return NULL;
    } else {
        return &udd_ep_job[(2 * (ep & USB_EP_ADDR_MASK) + ((ep & USB_EP_DIR_IN) ? 1 : 0)) - 2];
    }
}