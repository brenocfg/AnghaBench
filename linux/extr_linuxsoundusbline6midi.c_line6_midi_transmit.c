#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_line6 {int /*<<< orphan*/  max_packet_size; struct snd_line6_midi* line6midi; } ;
struct snd_rawmidi_substream {int dummy; } ;
struct midi_buffer {int dummy; } ;
struct snd_line6_midi {struct midi_buffer midibuf_out; } ;
struct TYPE_2__ {struct usb_line6* line6; } ;

/* Variables and functions */
 int LINE6_FALLBACK_MAXPACKETSIZE ; 
 int /*<<< orphan*/  line6_midibuf_bytes_free (struct midi_buffer*) ; 
 int line6_midibuf_read (struct midi_buffer*,unsigned char*,int) ; 
 int /*<<< orphan*/  line6_midibuf_write (struct midi_buffer*,unsigned char*,int) ; 
 TYPE_1__* line6_rawmidi_substream_midi (struct snd_rawmidi_substream*) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_midi_async (struct usb_line6*,unsigned char*,int) ; 
 int /*<<< orphan*/  snd_rawmidi_transmit_ack (struct snd_rawmidi_substream*,int) ; 
 int snd_rawmidi_transmit_peek (struct snd_rawmidi_substream*,unsigned char*,int) ; 

__attribute__((used)) static void line6_midi_transmit(struct snd_rawmidi_substream *substream)
{
	struct usb_line6 *line6 =
	    line6_rawmidi_substream_midi(substream)->line6;
	struct snd_line6_midi *line6midi = line6->line6midi;
	struct midi_buffer *mb = &line6midi->midibuf_out;
	unsigned char chunk[LINE6_FALLBACK_MAXPACKETSIZE];
	int req, done;

	for (;;) {
		req = min(line6_midibuf_bytes_free(mb), line6->max_packet_size);
		done = snd_rawmidi_transmit_peek(substream, chunk, req);

		if (done == 0)
			break;

		line6_midibuf_write(mb, chunk, done);
		snd_rawmidi_transmit_ack(substream, done);
	}

	for (;;) {
		done = line6_midibuf_read(mb, chunk,
					  LINE6_FALLBACK_MAXPACKETSIZE);

		if (done == 0)
			break;

		send_midi_async(line6, chunk, done);
	}
}