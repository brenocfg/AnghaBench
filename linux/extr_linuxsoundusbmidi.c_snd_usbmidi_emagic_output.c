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
struct usbmidi_out_port {int /*<<< orphan*/  substream; scalar_t__ active; } ;
struct urb {int* transfer_buffer; int transfer_buffer_length; } ;
struct snd_usb_midi_out_endpoint {int current_port; int max_transfer; struct usbmidi_out_port* ports; } ;

/* Variables and functions */
 int snd_rawmidi_transmit (int /*<<< orphan*/ ,int*,int) ; 
 int snd_rawmidi_transmit_peek (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void snd_usbmidi_emagic_output(struct snd_usb_midi_out_endpoint *ep,
				      struct urb *urb)
{
	int port0 = ep->current_port;
	uint8_t *buf = urb->transfer_buffer;
	int buf_free = ep->max_transfer;
	int length, i;

	for (i = 0; i < 0x10; ++i) {
		/* round-robin, starting at the last current port */
		int portnum = (port0 + i) & 15;
		struct usbmidi_out_port *port = &ep->ports[portnum];

		if (!port->active)
			continue;
		if (snd_rawmidi_transmit_peek(port->substream, buf, 1) != 1) {
			port->active = 0;
			continue;
		}

		if (portnum != ep->current_port) {
			if (buf_free < 2)
				break;
			ep->current_port = portnum;
			buf[0] = 0xf5;
			buf[1] = (portnum + 1) & 15;
			buf += 2;
			buf_free -= 2;
		}

		if (buf_free < 1)
			break;
		length = snd_rawmidi_transmit(port->substream, buf, buf_free);
		if (length > 0) {
			buf += length;
			buf_free -= length;
			if (buf_free < 1)
				break;
		}
	}
	if (buf_free < ep->max_transfer && buf_free > 0) {
		*buf = 0xff;
		--buf_free;
	}
	urb->transfer_buffer_length = ep->max_transfer - buf_free;
}