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
struct echoaudio {struct snd_rawmidi_substream* midi_in; } ;
struct TYPE_2__ {struct echoaudio* private_data; } ;

/* Variables and functions */

__attribute__((used)) static int snd_echo_midi_input_open(struct snd_rawmidi_substream *substream)
{
	struct echoaudio *chip = substream->rmidi->private_data;

	chip->midi_in = substream;
	return 0;
}