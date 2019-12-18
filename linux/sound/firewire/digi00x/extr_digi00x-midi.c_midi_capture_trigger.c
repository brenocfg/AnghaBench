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
struct snd_rawmidi_substream {unsigned int number; TYPE_1__* rmidi; } ;
struct snd_dg00x {int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_stream; } ;
struct TYPE_2__ {scalar_t__ device; struct snd_dg00x* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdtp_dot_midi_trigger (int /*<<< orphan*/ *,unsigned int,struct snd_rawmidi_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void midi_capture_trigger(struct snd_rawmidi_substream *substream,
				 int up)
{
	struct snd_dg00x *dg00x = substream->rmidi->private_data;
	unsigned int port;
	unsigned long flags;

	if (substream->rmidi->device == 0)
		port = substream->number;
	else
		port = 2;

	spin_lock_irqsave(&dg00x->lock, flags);

	if (up)
		amdtp_dot_midi_trigger(&dg00x->tx_stream, port, substream);
	else
		amdtp_dot_midi_trigger(&dg00x->tx_stream, port, NULL);

	spin_unlock_irqrestore(&dg00x->lock, flags);
}