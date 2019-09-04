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
struct usb_line6 {int /*<<< orphan*/  card; } ;
struct usb_line6_podhd {struct usb_line6 line6; } ;

/* Variables and functions */
 int snd_card_register (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int podhd_startup_finalize(struct usb_line6_podhd *pod)
{
	struct usb_line6 *line6 = &pod->line6;

	/* ALSA audio interface: */
	return snd_card_register(line6->card);
}