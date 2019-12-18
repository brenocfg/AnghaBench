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
typedef  int /*<<< orphan*/  u8 ;
struct snd_rawmidi_substream {scalar_t__ number; TYPE_1__* rmidi; } ;
struct mts64 {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct mts64* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mts64_write_midi (struct mts64*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  snd_rawmidi_transmit_ack (struct snd_rawmidi_substream*,int) ; 
 int snd_rawmidi_transmit_peek (struct snd_rawmidi_substream*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_mts64_rawmidi_output_trigger(struct snd_rawmidi_substream *substream,
					     int up)
{
	struct mts64 *mts = substream->rmidi->private_data;
	u8 data;
	unsigned long flags;

	spin_lock_irqsave(&mts->lock, flags);
	while (snd_rawmidi_transmit_peek(substream, &data, 1) == 1) {
		mts64_write_midi(mts, data, substream->number+1);
		snd_rawmidi_transmit_ack(substream, 1);
	}
	spin_unlock_irqrestore(&mts->lock, flags);
}