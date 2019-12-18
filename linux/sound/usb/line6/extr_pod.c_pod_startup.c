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
struct usb_line6_pod {int startup_progress; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  line6; } ;
struct usb_line6 {int /*<<< orphan*/  ifcdev; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int POD_STARTUP_DONE ; 
#define  POD_STARTUP_SETUP 129 
#define  POD_STARTUP_VERSIONREQ 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  line6_read_serial_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct usb_line6_pod* line6_to_pod (struct usb_line6*) ; 
 int /*<<< orphan*/  line6_version_request_async (struct usb_line6*) ; 
 int /*<<< orphan*/  snd_card_register (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pod_startup(struct usb_line6 *line6)
{
	struct usb_line6_pod *pod = line6_to_pod(line6);

	switch (pod->startup_progress) {
	case POD_STARTUP_VERSIONREQ:
		/* request firmware version: */
		line6_version_request_async(line6);
		break;
	case POD_STARTUP_SETUP:
		/* serial number: */
		line6_read_serial_number(&pod->line6, &pod->serial_number);

		/* ALSA audio interface: */
		if (snd_card_register(line6->card))
			dev_err(line6->ifcdev, "Failed to register POD card.\n");
		pod->startup_progress = POD_STARTUP_DONE;
		break;
	default:
		break;
	}
}