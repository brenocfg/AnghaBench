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
struct mts64 {scalar_t__ open_count; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct mts64* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mts64_device_close (struct mts64*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_mts64_rawmidi_close(struct snd_rawmidi_substream *substream)
{
	struct mts64 *mts = substream->rmidi->private_data;
	unsigned long flags;

	--(mts->open_count);
	if (mts->open_count == 0) {
		/* We need the spinlock_irqsave here because we can still
		   have IRQs at this point */
		spin_lock_irqsave(&mts->lock, flags);
		mts64_device_close(mts);
		spin_unlock_irqrestore(&mts->lock, flags);

		msleep(500);

	} else if (mts->open_count < 0)
		mts->open_count = 0;

	return 0;
}