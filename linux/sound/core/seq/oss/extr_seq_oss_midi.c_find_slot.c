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
struct seq_oss_midi {int client; int port; int /*<<< orphan*/  use_lock; } ;

/* Variables and functions */
 int max_midi_devs ; 
 struct seq_oss_midi** midi_devs ; 
 int /*<<< orphan*/  register_lock ; 
 int /*<<< orphan*/  snd_use_lock_use (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct seq_oss_midi *
find_slot(int client, int port)
{
	int i;
	struct seq_oss_midi *mdev;
	unsigned long flags;

	spin_lock_irqsave(&register_lock, flags);
	for (i = 0; i < max_midi_devs; i++) {
		mdev = midi_devs[i];
		if (mdev && mdev->client == client && mdev->port == port) {
			/* found! */
			snd_use_lock_use(&mdev->use_lock);
			spin_unlock_irqrestore(&register_lock, flags);
			return mdev;
		}
	}
	spin_unlock_irqrestore(&register_lock, flags);
	return NULL;
}