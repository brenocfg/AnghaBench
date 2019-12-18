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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int E_DN1_N; scalar_t__ E_VBUS_1; scalar_t__ E_VBUS_2; } ;
struct TYPE_4__ {TYPE_1__ bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_print (char*) ; 
 int /*<<< orphan*/  SR_EXP_WriteData () ; 
 scalar_t__ USB_EXTRA_STATE_DISABLED ; 
 scalar_t__ USB_EXTRA_STATE_DISABLED_UNTIL_REPLUG ; 
 scalar_t__ USB_EXTRA_STATE_ENABLED ; 
 scalar_t__ USB_HOST_PORT_1 ; 
 scalar_t__ USB_HOST_PORT_2 ; 
 int /*<<< orphan*/  gcr_breathe ; 
 int /*<<< orphan*/  gcr_desired ; 
 scalar_t__ led_animation_breathing ; 
 TYPE_2__ sr_exp_data ; 
 scalar_t__ usb_extra_state ; 
 scalar_t__ usb_host_port ; 

void USB_ExtraSetState(uint8_t state) {
    uint8_t state_save = state;

    if (state == USB_EXTRA_STATE_DISABLED_UNTIL_REPLUG) state = USB_EXTRA_STATE_DISABLED;

    if (usb_host_port == USB_HOST_PORT_1)
        sr_exp_data.bit.E_VBUS_2 = state;
    else if (usb_host_port == USB_HOST_PORT_2)
        sr_exp_data.bit.E_VBUS_1 = state;
    else
        return;

    sr_exp_data.bit.E_DN1_N = !state;
    SR_EXP_WriteData();

    usb_extra_state = state_save;

    if (usb_extra_state == USB_EXTRA_STATE_ENABLED)
        CDC_print("USB: Extra enabled\r\n");
    else if (usb_extra_state == USB_EXTRA_STATE_DISABLED) {
        CDC_print("USB: Extra disabled\r\n");
#    ifdef USE_MASSDROP_CONFIGURATOR
        if (led_animation_breathing) gcr_breathe = gcr_desired;
#    endif
    } else if (usb_extra_state == USB_EXTRA_STATE_DISABLED_UNTIL_REPLUG)
        CDC_print("USB: Extra disabled until replug\r\n");
    else
        CDC_print("USB: Extra state unknown\r\n");
}