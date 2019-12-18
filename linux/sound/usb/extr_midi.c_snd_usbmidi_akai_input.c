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
 int /*<<< orphan*/  snd_usbmidi_input_data (struct snd_usb_midi_in_endpoint*,int /*<<< orphan*/ ,int*,unsigned int) ; 

__attribute__((used)) static void snd_usbmidi_akai_input(struct snd_usb_midi_in_endpoint *ep,
				   uint8_t *buffer, int buffer_length)
{
	unsigned int pos = 0;
	unsigned int len = (unsigned int)buffer_length;
	while (pos < len) {
		unsigned int port = (buffer[pos] >> 4) - 1;
		unsigned int msg_len = buffer[pos] & 0x0f;
		pos++;
		if (pos + msg_len <= len && port < 2)
			snd_usbmidi_input_data(ep, 0, &buffer[pos], msg_len);
		pos += msg_len;
	}
}