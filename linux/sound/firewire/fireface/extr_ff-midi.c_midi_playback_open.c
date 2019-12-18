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
struct snd_rawmidi_substream {size_t number; TYPE_1__* rmidi; } ;
struct snd_ff {int* rx_midi_error; int /*<<< orphan*/ * rx_midi_substreams; scalar_t__* on_sysex; } ;
struct TYPE_2__ {struct snd_ff* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,struct snd_rawmidi_substream*) ; 

__attribute__((used)) static int midi_playback_open(struct snd_rawmidi_substream *substream)
{
	struct snd_ff *ff = substream->rmidi->private_data;

	/* Initialize internal status. */
	ff->on_sysex[substream->number] = 0;
	ff->rx_midi_error[substream->number] = false;

	WRITE_ONCE(ff->rx_midi_substreams[substream->number], substream);

	return 0;
}