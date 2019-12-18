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
struct usb_config {int run_in_standby; int /*<<< orphan*/  speed_mode; scalar_t__ source_generator; scalar_t__ select_host_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (struct usb_config*) ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 

void usb_get_config_defaults(struct usb_config *module_config) {
    Assert(module_config);

    /* Sanity check arguments */
    Assert(module_config);
    /* Write default configuration to config struct */
    module_config->select_host_mode = 0;
    module_config->run_in_standby   = 1;
    module_config->source_generator = 0;
    module_config->speed_mode       = USB_SPEED_FULL;
}