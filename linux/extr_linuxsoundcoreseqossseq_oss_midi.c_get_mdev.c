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
struct seq_oss_midi {int /*<<< orphan*/  use_lock; } ;

/* Variables and functions */
 struct seq_oss_midi** midi_devs ; 
 int /*<<< orphan*/  register_lock ; 
 int /*<<< orphan*/  snd_use_lock_use (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct seq_oss_midi *
get_mdev(int dev)
{
	struct seq_oss_midi *mdev;
	unsigned long flags;

	spin_lock_irqsave(&register_lock, flags);
	mdev = midi_devs[dev];
	if (mdev)
		snd_use_lock_use(&mdev->use_lock);
	spin_unlock_irqrestore(&register_lock, flags);
	return mdev;
}