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
struct seq_oss_midi {int /*<<< orphan*/  coder; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct seq_oss_midi*) ; 
 int max_midi_devs ; 
 struct seq_oss_midi** midi_devs ; 
 int /*<<< orphan*/  register_lock ; 
 int /*<<< orphan*/  snd_midi_event_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
snd_seq_oss_midi_clear_all(void)
{
	int i;
	struct seq_oss_midi *mdev;
	unsigned long flags;

	spin_lock_irqsave(&register_lock, flags);
	for (i = 0; i < max_midi_devs; i++) {
		if ((mdev = midi_devs[i]) != NULL) {
			snd_midi_event_free(mdev->coder);
			kfree(mdev);
			midi_devs[i] = NULL;
		}
	}
	max_midi_devs = 0;
	spin_unlock_irqrestore(&register_lock, flags);
}