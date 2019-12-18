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
struct mts64 {int /*<<< orphan*/  lock; int /*<<< orphan*/ * mode; } ;
struct TYPE_2__ {struct mts64* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTS64_MODE_INPUT_TRIGGERED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_mts64_rawmidi_input_trigger(struct snd_rawmidi_substream *substream,
					    int up)
{
	struct mts64 *mts = substream->rmidi->private_data;
	unsigned long flags;

	spin_lock_irqsave(&mts->lock, flags);
	if (up)
		mts->mode[substream->number] |= MTS64_MODE_INPUT_TRIGGERED;
	else
 		mts->mode[substream->number] &= ~MTS64_MODE_INPUT_TRIGGERED;
	
	spin_unlock_irqrestore(&mts->lock, flags);
}