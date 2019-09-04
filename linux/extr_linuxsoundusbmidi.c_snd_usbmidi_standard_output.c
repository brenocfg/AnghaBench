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
typedef  int /*<<< orphan*/  uint8_t ;
struct usbmidi_out_port {scalar_t__ active; int /*<<< orphan*/  substream; } ;
struct urb {scalar_t__ transfer_buffer_length; } ;
struct snd_usb_midi_out_endpoint {scalar_t__ max_transfer; struct usbmidi_out_port* ports; } ;

/* Variables and functions */
 int snd_rawmidi_transmit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_usbmidi_transmit_byte (struct usbmidi_out_port*,int /*<<< orphan*/ ,struct urb*) ; 

__attribute__((used)) static void snd_usbmidi_standard_output(struct snd_usb_midi_out_endpoint *ep,
					struct urb *urb)
{
	int p;

	/* FIXME: lower-numbered ports can starve higher-numbered ports */
	for (p = 0; p < 0x10; ++p) {
		struct usbmidi_out_port *port = &ep->ports[p];
		if (!port->active)
			continue;
		while (urb->transfer_buffer_length + 3 < ep->max_transfer) {
			uint8_t b;
			if (snd_rawmidi_transmit(port->substream, &b, 1) != 1) {
				port->active = 0;
				break;
			}
			snd_usbmidi_transmit_byte(port, b, urb);
		}
	}
}