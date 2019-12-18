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
typedef  int u8 ;
struct snd_rawmidi_substream {int number; } ;
struct snd_fw_async_midi_port {int* buf; int on_sysex; int running_status; } ;

/* Variables and functions */
 int calculate_message_bytes (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int snd_rawmidi_transmit_peek (struct snd_rawmidi_substream*,int*,int) ; 

__attribute__((used)) static int fill_message(struct snd_fw_async_midi_port *port,
			struct snd_rawmidi_substream *substream)
{
	int i, len, consume;
	u8 *label, *msg;
	u8 status;

	/* The first byte is used for label, the rest for MIDI bytes. */
	label = port->buf;
	msg = port->buf + 1;

	consume = snd_rawmidi_transmit_peek(substream, msg, 3);
	if (consume == 0)
		return 0;

	/* On exclusive message. */
	if (port->on_sysex) {
		/* Seek the end of exclusives. */
		for (i = 0; i < consume; ++i) {
			if (msg[i] == 0xf7) {
				port->on_sysex = false;
				break;
			}
		}

		/* At the end of exclusive message, use label 0x07. */
		if (!port->on_sysex) {
			consume = i + 1;
			*label = (substream->number << 4) | 0x07;
		/* During exclusive message, use label 0x04. */
		} else if (consume == 3) {
			*label = (substream->number << 4) | 0x04;
		/* We need to fill whole 3 bytes. Go to next change. */
		} else {
			return 0;
		}

		len = consume;
	} else {
		/* The beginning of exclusives. */
		if (msg[0] == 0xf0) {
			/* Transfer it in next chance in another condition. */
			port->on_sysex = true;
			return 0;
		} else {
			/* On running-status. */
			if ((msg[0] & 0x80) != 0x80)
				status = port->running_status;
			else
				status = msg[0];

			/* Calculate consume bytes. */
			len = calculate_message_bytes(status);
			if (len <= 0)
				return 0;

			/* On running-status. */
			if ((msg[0] & 0x80) != 0x80) {
				/* Enough MIDI bytes were not retrieved. */
				if (consume < len - 1)
					return 0;
				consume = len - 1;

				msg[2] = msg[1];
				msg[1] = msg[0];
				msg[0] = port->running_status;
			} else {
				/* Enough MIDI bytes were not retrieved. */
				if (consume < len)
					return 0;
				consume = len;

				port->running_status = msg[0];
			}
		}

		*label = (substream->number << 4) | (msg[0] >> 4);
	}

	if (len > 0 && len < 3)
		memset(msg + len, 0, 3 - len);

	return consume;
}