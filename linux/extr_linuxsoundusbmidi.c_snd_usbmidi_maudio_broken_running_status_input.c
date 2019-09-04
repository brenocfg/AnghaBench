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
typedef  size_t u8 ;
struct usbmidi_in_port {int running_status_length; } ;
struct snd_usb_midi_in_endpoint {struct usbmidi_in_port* ports; } ;

/* Variables and functions */
 int* snd_usbmidi_cin_length ; 
 int /*<<< orphan*/  snd_usbmidi_input_data (struct snd_usb_midi_in_endpoint*,int,int*,int) ; 

__attribute__((used)) static void snd_usbmidi_maudio_broken_running_status_input(
					struct snd_usb_midi_in_endpoint *ep,
					uint8_t *buffer, int buffer_length)
{
	int i;

	for (i = 0; i + 3 < buffer_length; i += 4)
		if (buffer[i] != 0) {
			int cable = buffer[i] >> 4;
			u8 cin = buffer[i] & 0x0f;
			struct usbmidi_in_port *port = &ep->ports[cable];
			int length;

			length = snd_usbmidi_cin_length[cin];
			if (cin == 0xf && buffer[i + 1] >= 0xf8)
				; /* realtime msg: no running status change */
			else if (cin >= 0x8 && cin <= 0xe)
				/* channel msg */
				port->running_status_length = length - 1;
			else if (cin == 0x4 &&
				 port->running_status_length != 0 &&
				 buffer[i + 1] < 0x80)
				/* CIN 4 that is not a SysEx */
				length = port->running_status_length;
			else
				/*
				 * All other msgs cannot begin running status.
				 * (A channel msg sent as two or three CIN 0xF
				 * packets could in theory, but this device
				 * doesn't use this format.)
				 */
				port->running_status_length = 0;
			snd_usbmidi_input_data(ep, cable, &buffer[i + 1],
					       length);
		}
}