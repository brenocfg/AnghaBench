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
struct usb_device_endpoint_config {int auto_zlp; int /*<<< orphan*/  ep_type; int /*<<< orphan*/  ep_size; scalar_t__ ep_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (struct usb_device_endpoint_config*) ; 
 int /*<<< orphan*/  USB_DEVICE_ENDPOINT_TYPE_CONTROL ; 
 int /*<<< orphan*/  USB_ENDPOINT_8_BYTE ; 

void usb_device_endpoint_get_config_defaults(struct usb_device_endpoint_config *ep_config) {
    /* Sanity check arguments */
    Assert(ep_config);

    /* Write default config to config struct */
    ep_config->ep_address = 0;
    ep_config->ep_size    = USB_ENDPOINT_8_BYTE;
    ep_config->auto_zlp   = false;
    ep_config->ep_type    = USB_DEVICE_ENDPOINT_TYPE_CONTROL;
}