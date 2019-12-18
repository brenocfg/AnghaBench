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
struct amdtp_stream {int flags; int /*<<< orphan*/  data_block_quadlets; struct amdtp_am824* protocol; } ;
struct amdtp_am824 {size_t midi_position; scalar_t__* midi; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int CIP_UNALIGHED_DBC ; 
 int /*<<< orphan*/  snd_rawmidi_receive (scalar_t__,int*,int) ; 

__attribute__((used)) static void read_midi_messages(struct amdtp_stream *s, __be32 *buffer,
			unsigned int frames, unsigned int data_block_counter)
{
	struct amdtp_am824 *p = s->protocol;
	int len;
	u8 *b;
	int f;

	for (f = 0; f < frames; f++) {
		unsigned int port = f;

		if (!(s->flags & CIP_UNALIGHED_DBC))
			port += data_block_counter;
		port %= 8;
		b = (u8 *)&buffer[p->midi_position];

		len = b[0] - 0x80;
		if ((1 <= len) &&  (len <= 3) && (p->midi[port]))
			snd_rawmidi_receive(p->midi[port], b + 1, len);

		buffer += s->data_block_quadlets;
	}
}