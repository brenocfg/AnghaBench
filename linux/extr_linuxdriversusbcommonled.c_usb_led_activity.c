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
struct led_trigger {int dummy; } ;
typedef  enum usb_led_event { ____Placeholder_usb_led_event } usb_led_event ;

/* Variables and functions */
#define  USB_LED_EVENT_GADGET 129 
#define  USB_LED_EVENT_HOST 128 
 int /*<<< orphan*/  led_trigger_blink_oneshot (struct led_trigger*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct led_trigger* ledtrig_usb_gadget ; 
 struct led_trigger* ledtrig_usb_host ; 
 int /*<<< orphan*/  usb_blink_delay ; 

void usb_led_activity(enum usb_led_event ev)
{
	struct led_trigger *trig = NULL;

	switch (ev) {
	case USB_LED_EVENT_GADGET:
		trig = ledtrig_usb_gadget;
		break;
	case USB_LED_EVENT_HOST:
		trig = ledtrig_usb_host;
		break;
	}
	/* led_trigger_blink_oneshot() handles trig == NULL gracefully */
	led_trigger_blink_oneshot(trig, &usb_blink_delay, &usb_blink_delay, 0);
}