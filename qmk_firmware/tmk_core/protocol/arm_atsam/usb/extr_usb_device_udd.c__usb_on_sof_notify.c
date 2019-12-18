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
struct usb_module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDC_SOF_EVENT () ; 
 int /*<<< orphan*/  udc_sof_notify () ; 

__attribute__((used)) static void _usb_on_sof_notify(struct usb_module *module_inst, void *pointer) {
    udc_sof_notify();
#ifdef UDC_SOF_EVENT
    UDC_SOF_EVENT();
#endif
}