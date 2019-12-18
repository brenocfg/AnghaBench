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
struct snd_usb_midi_out_endpoint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_usbmidi_do_output (struct snd_usb_midi_out_endpoint*) ; 

__attribute__((used)) static void snd_usbmidi_out_tasklet(unsigned long data)
{
	struct snd_usb_midi_out_endpoint *ep =
		(struct snd_usb_midi_out_endpoint *) data;

	snd_usbmidi_do_output(ep);
}