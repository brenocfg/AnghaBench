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
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct bcd2000 {struct snd_rawmidi_substream* midi_receive_substream; } ;
struct TYPE_2__ {struct bcd2000* private_data; } ;

/* Variables and functions */

__attribute__((used)) static void bcd2000_midi_input_trigger(struct snd_rawmidi_substream *substream,
						int up)
{
	struct bcd2000 *bcd2k = substream->rmidi->private_data;
	bcd2k->midi_receive_substream = up ? substream : NULL;
}