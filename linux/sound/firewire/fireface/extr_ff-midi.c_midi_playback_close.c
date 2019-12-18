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
struct snd_ff {int /*<<< orphan*/ * rx_midi_substreams; int /*<<< orphan*/ * rx_midi_work; } ;
struct TYPE_2__ {struct snd_ff* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int midi_playback_close(struct snd_rawmidi_substream *substream)
{
	struct snd_ff *ff = substream->rmidi->private_data;

	cancel_work_sync(&ff->rx_midi_work[substream->number]);
	WRITE_ONCE(ff->rx_midi_substreams[substream->number], NULL);

	return 0;
}