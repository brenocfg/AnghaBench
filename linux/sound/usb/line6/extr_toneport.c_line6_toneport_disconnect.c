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
struct usb_line6_toneport {int dummy; } ;
struct usb_line6 {int dummy; } ;

/* Variables and functions */
 struct usb_line6_toneport* line6_to_toneport (struct usb_line6*) ; 
 scalar_t__ toneport_has_led (struct usb_line6_toneport*) ; 
 int /*<<< orphan*/  toneport_remove_leds (struct usb_line6_toneport*) ; 

__attribute__((used)) static void line6_toneport_disconnect(struct usb_line6 *line6)
{
	struct usb_line6_toneport *toneport = line6_to_toneport(line6);

	if (toneport_has_led(toneport))
		toneport_remove_leds(toneport);
}