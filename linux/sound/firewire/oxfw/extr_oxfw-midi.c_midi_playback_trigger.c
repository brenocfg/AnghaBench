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
struct snd_rawmidi_substream {int /*<<< orphan*/  number; TYPE_1__* rmidi; } ;
struct snd_oxfw {int /*<<< orphan*/  lock; int /*<<< orphan*/  rx_stream; } ;
struct TYPE_2__ {struct snd_oxfw* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_am824_midi_trigger (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct snd_rawmidi_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void midi_playback_trigger(struct snd_rawmidi_substream *substrm, int up)
{
	struct snd_oxfw *oxfw = substrm->rmidi->private_data;
	unsigned long flags;

	spin_lock_irqsave(&oxfw->lock, flags);

	if (up)
		amdtp_am824_midi_trigger(&oxfw->rx_stream,
					 substrm->number, substrm);
	else
		amdtp_am824_midi_trigger(&oxfw->rx_stream,
					 substrm->number, NULL);

	spin_unlock_irqrestore(&oxfw->lock, flags);
}