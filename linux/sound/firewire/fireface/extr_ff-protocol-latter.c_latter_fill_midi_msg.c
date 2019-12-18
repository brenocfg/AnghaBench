#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ u32 ;
struct snd_rawmidi_substream {int dummy; } ;
struct snd_ff {int* on_sysex; int* rx_bytes; int /*<<< orphan*/ ** msg_buf; } ;

/* Variables and functions */
 int calculate_message_bytes (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (TYPE_1__) ; 
 int snd_rawmidi_transmit_peek (struct snd_rawmidi_substream*,int*,int) ; 

__attribute__((used)) static int latter_fill_midi_msg(struct snd_ff *ff,
				struct snd_rawmidi_substream *substream,
				unsigned int port)
{
	u32 data = {0};
	u8 *buf = (u8 *)&data;
	int consumed;

	buf[0] = port << 4;
	consumed = snd_rawmidi_transmit_peek(substream, buf + 1, 3);
	if (consumed <= 0)
		return consumed;

	if (!ff->on_sysex[port]) {
		if (buf[1] != 0xf0) {
			if (consumed < calculate_message_bytes(buf[1]))
				return 0;
		} else {
			// The beginning of exclusives.
			ff->on_sysex[port] = true;
		}

		buf[0] |= consumed;
	} else {
		if (buf[1] != 0xf7) {
			if (buf[2] == 0xf7 || buf[3] == 0xf7) {
				// Transfer end code at next time.
				consumed -= 1;
			}

			buf[0] |= consumed;
		} else {
			// The end of exclusives.
			ff->on_sysex[port] = false;
			consumed = 1;
			buf[0] |= 0x0f;
		}
	}

	ff->msg_buf[port][0] = cpu_to_le32(data);
	ff->rx_bytes[port] = consumed;

	return 1;
}