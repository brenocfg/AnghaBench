#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  card; } ;
struct usb_line6_variax {int startup_progress; TYPE_1__ line6; } ;
struct usb_line6 {int /*<<< orphan*/  startup_work; } ;

/* Variables and functions */
#define  VARIAX_STARTUP_ACTIVATE 130 
 int /*<<< orphan*/  VARIAX_STARTUP_DELAY1 ; 
 int /*<<< orphan*/  VARIAX_STARTUP_DELAY4 ; 
#define  VARIAX_STARTUP_SETUP 129 
#define  VARIAX_STARTUP_VERSIONREQ 128 
 struct usb_line6_variax* line6_to_variax (struct usb_line6*) ; 
 int /*<<< orphan*/  line6_version_request_async (struct usb_line6*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_card_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  variax_activate_async (struct usb_line6_variax*,int) ; 

__attribute__((used)) static void variax_startup(struct usb_line6 *line6)
{
	struct usb_line6_variax *variax = line6_to_variax(line6);

	switch (variax->startup_progress) {
	case VARIAX_STARTUP_VERSIONREQ:
		/* repeat request until getting the response */
		schedule_delayed_work(&line6->startup_work,
				      msecs_to_jiffies(VARIAX_STARTUP_DELAY1));
		/* request firmware version: */
		line6_version_request_async(line6);
		break;
	case VARIAX_STARTUP_ACTIVATE:
		/* activate device: */
		variax_activate_async(variax, 1);
		variax->startup_progress = VARIAX_STARTUP_SETUP;
		schedule_delayed_work(&line6->startup_work,
				      msecs_to_jiffies(VARIAX_STARTUP_DELAY4));
		break;
	case VARIAX_STARTUP_SETUP:
		/* ALSA audio interface: */
		snd_card_register(variax->line6.card);
		break;
	}
}