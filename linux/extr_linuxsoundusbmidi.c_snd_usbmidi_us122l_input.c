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
typedef  int uint8_t ;
struct snd_usb_midi_in_endpoint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_usbmidi_input_data (struct snd_usb_midi_in_endpoint*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void snd_usbmidi_us122l_input(struct snd_usb_midi_in_endpoint *ep,
				     uint8_t *buffer, int buffer_length)
{
	if (buffer_length != 9)
		return;
	buffer_length = 8;
	while (buffer_length && buffer[buffer_length - 1] == 0xFD)
		buffer_length--;
	if (buffer_length)
		snd_usbmidi_input_data(ep, 0, buffer, buffer_length);
}