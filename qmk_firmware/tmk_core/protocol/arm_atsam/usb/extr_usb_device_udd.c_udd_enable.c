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
typedef  int /*<<< orphan*/  uint32_t ;
struct usb_config {int /*<<< orphan*/  source_generator; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDD_CLOCK_GEN ; 
 int /*<<< orphan*/  UDD_STATE_SUSPEND ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  __DMB () ; 
 int /*<<< orphan*/  __disable_irq () ; 
 int /*<<< orphan*/  __get_PRIMASK () ; 
 int /*<<< orphan*/  __set_PRIMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udd_attach () ; 
 int /*<<< orphan*/  udd_sleep_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udd_wait_clock_ready () ; 
 int /*<<< orphan*/  usb_device ; 
 int /*<<< orphan*/  usb_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_get_config_defaults (struct usb_config*) ; 
 int /*<<< orphan*/  usb_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct usb_config*) ; 

void udd_enable(void) {
    uint32_t irqflags;

    /* To avoid USB interrupt before end of initialization */
    irqflags = __get_PRIMASK();
    __disable_irq();
    __DMB();

    struct usb_config config_usb;

    /* USB Module configuration */
    usb_get_config_defaults(&config_usb);
    config_usb.source_generator = UDD_CLOCK_GEN;
    usb_init(&usb_device, USB, &config_usb);

    /* USB Module Enable */
    usb_enable(&usb_device);

    /* Check clock after enable module, request the clock */
    udd_wait_clock_ready();

    udd_sleep_mode(UDD_STATE_SUSPEND);

    // No VBus detect, assume always high
#ifndef USB_DEVICE_ATTACH_AUTO_DISABLE
    udd_attach();
#endif

    __DMB();
    __set_PRIMASK(irqflags);
}