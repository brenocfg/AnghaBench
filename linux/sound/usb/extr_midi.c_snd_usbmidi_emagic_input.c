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
struct snd_usb_midi_in_endpoint {int seen_f5; int current_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_usbmidi_input_data (struct snd_usb_midi_in_endpoint*,int,int*,int) ; 

__attribute__((used)) static void snd_usbmidi_emagic_input(struct snd_usb_midi_in_endpoint *ep,
				     uint8_t *buffer, int buffer_length)
{
	int i;

	/* FF indicates end of valid data */
	for (i = 0; i < buffer_length; ++i)
		if (buffer[i] == 0xff) {
			buffer_length = i;
			break;
		}

	/* handle F5 at end of last buffer */
	if (ep->seen_f5)
		goto switch_port;

	while (buffer_length > 0) {
		/* determine size of data until next F5 */
		for (i = 0; i < buffer_length; ++i)
			if (buffer[i] == 0xf5)
				break;
		snd_usbmidi_input_data(ep, ep->current_port, buffer, i);
		buffer += i;
		buffer_length -= i;

		if (buffer_length <= 0)
			break;
		/* assert(buffer[0] == 0xf5); */
		ep->seen_f5 = 1;
		++buffer;
		--buffer_length;

	switch_port:
		if (buffer_length <= 0)
			break;
		if (buffer[0] < 0x80) {
			ep->current_port = (buffer[0] - 1) & 15;
			++buffer;
			--buffer_length;
		}
		ep->seen_f5 = 0;
	}
}