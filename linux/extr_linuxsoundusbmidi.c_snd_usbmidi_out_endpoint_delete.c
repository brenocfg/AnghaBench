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
 int /*<<< orphan*/  kfree (struct snd_usb_midi_out_endpoint*) ; 
 int /*<<< orphan*/  snd_usbmidi_out_endpoint_clear (struct snd_usb_midi_out_endpoint*) ; 

__attribute__((used)) static void snd_usbmidi_out_endpoint_delete(struct snd_usb_midi_out_endpoint *ep)
{
	snd_usbmidi_out_endpoint_clear(ep);
	kfree(ep);
}