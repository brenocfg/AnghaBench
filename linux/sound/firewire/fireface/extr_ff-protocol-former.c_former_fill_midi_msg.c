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
typedef  int /*<<< orphan*/  u8 ;
struct snd_rawmidi_substream {int dummy; } ;
struct snd_ff {int* rx_bytes; int /*<<< orphan*/ ** msg_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_FF_MAXIMIM_MIDI_QUADS ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int snd_rawmidi_transmit_peek (struct snd_rawmidi_substream*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int former_fill_midi_msg(struct snd_ff *ff,
				struct snd_rawmidi_substream *substream,
				unsigned int port)
{
	u8 *buf = (u8 *)ff->msg_buf[port];
	int len;
	int i;

	len = snd_rawmidi_transmit_peek(substream, buf,
					SND_FF_MAXIMIM_MIDI_QUADS);
	if (len <= 0)
		return len;

	// One quadlet includes one byte.
	for (i = len - 1; i >= 0; --i)
		ff->msg_buf[port][i] = cpu_to_le32(buf[i]);
	ff->rx_bytes[port] = len;

	return len;
}