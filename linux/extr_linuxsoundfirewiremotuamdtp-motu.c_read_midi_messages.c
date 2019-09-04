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
struct snd_rawmidi_substream {int dummy; } ;
struct amdtp_stream {int /*<<< orphan*/  data_block_quadlets; struct amdtp_motu* protocol; } ;
struct amdtp_motu {size_t midi_flag_offset; int midi_byte_offset; int /*<<< orphan*/  midi; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 struct snd_rawmidi_substream* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_receive (struct snd_rawmidi_substream*,int*,int) ; 

__attribute__((used)) static void read_midi_messages(struct amdtp_stream *s, __be32 *buffer,
			       unsigned int data_blocks)
{
	struct amdtp_motu *p = s->protocol;
	struct snd_rawmidi_substream *midi;
	u8 *b;
	int i;

	for (i = 0; i < data_blocks; i++) {
		b = (u8 *)buffer;
		midi = READ_ONCE(p->midi);

		if (midi && (b[p->midi_flag_offset] & 0x01))
			snd_rawmidi_receive(midi, b + p->midi_byte_offset, 1);

		buffer += s->data_block_quadlets;
	}
}