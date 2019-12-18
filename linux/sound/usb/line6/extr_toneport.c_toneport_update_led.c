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
struct TYPE_4__ {int /*<<< orphan*/  usbdev; } ;
struct usb_line6_toneport {TYPE_3__* leds; TYPE_1__ line6; } ;
struct TYPE_5__ {int brightness; } ;
struct TYPE_6__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  toneport_send_cmd (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void toneport_update_led(struct usb_line6_toneport *toneport)
{
	toneport_send_cmd(toneport->line6.usbdev,
			  (toneport->leds[0].dev.brightness << 8) | 0x0002,
			  toneport->leds[1].dev.brightness);
}