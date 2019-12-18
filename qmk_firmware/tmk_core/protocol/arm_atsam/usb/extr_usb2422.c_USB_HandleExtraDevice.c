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
typedef  double uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_CON1 ; 
 int /*<<< orphan*/  ADC_CON2 ; 
 double USB_EXTRA_ADC_THRESHOLD ; 
 scalar_t__ USB_EXTRA_STATE_DISABLED ; 
 scalar_t__ USB_EXTRA_STATE_DISABLED_UNTIL_REPLUG ; 
 scalar_t__ USB_EXTRA_STATE_ENABLED ; 
 int /*<<< orphan*/  USB_ExtraSetState (scalar_t__) ; 
 scalar_t__ USB_HOST_PORT_1 ; 
 scalar_t__ USB_HOST_PORT_2 ; 
 double adc_extra ; 
 double adc_get (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_extra_manual ; 
 scalar_t__ usb_extra_state ; 
 scalar_t__ usb_host_port ; 

void USB_HandleExtraDevice(void) {
    uint16_t adcval;

    if (usb_host_port == USB_HOST_PORT_1)
        adcval = adc_get(ADC_CON2);
    else if (usb_host_port == USB_HOST_PORT_2)
        adcval = adc_get(ADC_CON1);
    else
        return;

    adc_extra = adc_extra * 0.9 + adcval * 0.1;

    // Check for a forced disable state (such as overload prevention)
    if (usb_extra_state == USB_EXTRA_STATE_DISABLED_UNTIL_REPLUG) {
        // Detect unplug and reset state to disabled
        if (adc_extra > USB_EXTRA_ADC_THRESHOLD) usb_extra_state = USB_EXTRA_STATE_DISABLED;

        return;  // Return even if unplug detected
    }

    if (usb_extra_manual) {
        if (usb_extra_state == USB_EXTRA_STATE_DISABLED) USB_ExtraSetState(USB_EXTRA_STATE_ENABLED);

        return;
    }

    // dpf("a %i %i\r\n",adcval, adc_extra);
    if (usb_extra_state == USB_EXTRA_STATE_DISABLED && adc_extra < USB_EXTRA_ADC_THRESHOLD)
        USB_ExtraSetState(USB_EXTRA_STATE_ENABLED);
    else if (usb_extra_state == USB_EXTRA_STATE_ENABLED && adc_extra > USB_EXTRA_ADC_THRESHOLD)
        USB_ExtraSetState(USB_EXTRA_STATE_DISABLED);
}