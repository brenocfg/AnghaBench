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
struct fw_scs1x {int input_escape_count; } ;
typedef  int /*<<< orphan*/  eox ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  midi_input_escaped_byte (struct snd_rawmidi_substream*,int) ; 
 int /*<<< orphan*/  snd_rawmidi_receive (struct snd_rawmidi_substream*,int const*,int) ; 
 int* sysex_escape_prefix ; 

__attribute__((used)) static void midi_input_byte(struct fw_scs1x *scs,
			    struct snd_rawmidi_substream *stream, u8 byte)
{
	const u8 eox = 0xf7;

	if (scs->input_escape_count > 0) {
		midi_input_escaped_byte(stream, byte);
		scs->input_escape_count--;
		if (scs->input_escape_count == 0)
			snd_rawmidi_receive(stream, &eox, sizeof(eox));
	} else if (byte == 0xf9) {
		snd_rawmidi_receive(stream, sysex_escape_prefix,
				    ARRAY_SIZE(sysex_escape_prefix));
		midi_input_escaped_byte(stream, 0x00);
		midi_input_escaped_byte(stream, 0xf9);
		scs->input_escape_count = 3;
	} else {
		snd_rawmidi_receive(stream, &byte, 1);
	}
}