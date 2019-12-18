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
struct usb_line6_podhd {int /*<<< orphan*/  serial_number; int /*<<< orphan*/  line6; } ;
struct usb_line6 {int /*<<< orphan*/  ifcdev; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  line6_read_serial_number (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct usb_line6_podhd* line6_to_podhd (struct usb_line6*) ; 
 int /*<<< orphan*/  podhd_dev_start (struct usb_line6_podhd*) ; 
 scalar_t__ snd_card_register (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void podhd_startup(struct usb_line6 *line6)
{
	struct usb_line6_podhd *pod = line6_to_podhd(line6);

	podhd_dev_start(pod);
	line6_read_serial_number(&pod->line6, &pod->serial_number);
	if (snd_card_register(line6->card))
		dev_err(line6->ifcdev, "Failed to register POD HD card.\n");
}