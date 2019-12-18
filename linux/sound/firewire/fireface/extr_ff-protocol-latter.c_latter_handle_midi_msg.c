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
typedef  int u8 ;
typedef  int u32 ;
struct snd_rawmidi_substream {int dummy; } ;
struct snd_ff {int /*<<< orphan*/ * tx_midi_substreams; TYPE_1__* spec; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {unsigned int midi_in_ports; } ;

/* Variables and functions */
 struct snd_rawmidi_substream* READ_ONCE (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_receive (struct snd_rawmidi_substream*,int*,unsigned int) ; 

__attribute__((used)) static void latter_handle_midi_msg(struct snd_ff *ff, unsigned int offset,
				   __le32 *buf, size_t length)
{
	u32 data = le32_to_cpu(*buf);
	unsigned int index = (data & 0x000000f0) >> 4;
	u8 byte[3];
	struct snd_rawmidi_substream *substream;
	unsigned int len;

	if (index >= ff->spec->midi_in_ports)
		return;

	switch (data & 0x0000000f) {
	case 0x00000008:
	case 0x00000009:
	case 0x0000000a:
	case 0x0000000b:
	case 0x0000000e:
		len = 3;
		break;
	case 0x0000000c:
	case 0x0000000d:
		len = 2;
		break;
	default:
		len = data & 0x00000003;
		if (len == 0)
			len = 3;
		break;
	}

	byte[0] = (data & 0x0000ff00) >> 8;
	byte[1] = (data & 0x00ff0000) >> 16;
	byte[2] = (data & 0xff000000) >> 24;

	substream = READ_ONCE(ff->tx_midi_substreams[index]);
	if (substream)
		snd_rawmidi_receive(substream, byte, len);
}