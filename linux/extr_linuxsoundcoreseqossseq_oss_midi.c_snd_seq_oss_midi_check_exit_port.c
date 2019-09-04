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
struct seq_oss_midi {size_t seq_device; int /*<<< orphan*/  coder; int /*<<< orphan*/  use_lock; } ;

/* Variables and functions */
 struct seq_oss_midi* find_slot (int,int) ; 
 int /*<<< orphan*/  kfree (struct seq_oss_midi*) ; 
 int max_midi_devs ; 
 int /*<<< orphan*/ ** midi_devs ; 
 int /*<<< orphan*/  register_lock ; 
 int /*<<< orphan*/  snd_midi_event_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_use_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_use_lock_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
snd_seq_oss_midi_check_exit_port(int client, int port)
{
	struct seq_oss_midi *mdev;
	unsigned long flags;
	int index;

	if ((mdev = find_slot(client, port)) != NULL) {
		spin_lock_irqsave(&register_lock, flags);
		midi_devs[mdev->seq_device] = NULL;
		spin_unlock_irqrestore(&register_lock, flags);
		snd_use_lock_free(&mdev->use_lock);
		snd_use_lock_sync(&mdev->use_lock);
		snd_midi_event_free(mdev->coder);
		kfree(mdev);
	}
	spin_lock_irqsave(&register_lock, flags);
	for (index = max_midi_devs - 1; index >= 0; index--) {
		if (midi_devs[index])
			break;
	}
	max_midi_devs = index + 1;
	spin_unlock_irqrestore(&register_lock, flags);
	return 0;
}