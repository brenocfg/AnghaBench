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
struct amdtp_stream {int /*<<< orphan*/  data_block_quadlets; struct amdtp_am824* protocol; } ;
struct amdtp_am824 {size_t midi_position; int /*<<< orphan*/ ** midi; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int MAX_MIDI_RX_BLOCKS ; 
 int /*<<< orphan*/  midi_rate_use_one_byte (struct amdtp_stream*,unsigned int) ; 
 scalar_t__ midi_ratelimit_per_packet (struct amdtp_stream*,unsigned int) ; 
 int snd_rawmidi_transmit (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void write_midi_messages(struct amdtp_stream *s, __be32 *buffer,
			unsigned int frames, unsigned int data_block_counter)
{
	struct amdtp_am824 *p = s->protocol;
	unsigned int f, port;
	u8 *b;

	for (f = 0; f < frames; f++) {
		b = (u8 *)&buffer[p->midi_position];

		port = (data_block_counter + f) % 8;
		if (f < MAX_MIDI_RX_BLOCKS &&
		    midi_ratelimit_per_packet(s, port) &&
		    p->midi[port] != NULL &&
		    snd_rawmidi_transmit(p->midi[port], &b[1], 1) == 1) {
			midi_rate_use_one_byte(s, port);
			b[0] = 0x81;
		} else {
			b[0] = 0x80;
			b[1] = 0;
		}
		b[2] = 0;
		b[3] = 0;

		buffer += s->data_block_quadlets;
	}
}