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
struct TYPE_2__ {int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct snd_seq_port_info {int type; int capability; int /*<<< orphan*/  name; TYPE_1__ addr; } ;
struct seq_oss_midi {int flags; int seq_device; int /*<<< orphan*/  coder; int /*<<< orphan*/  name; int /*<<< orphan*/  use_lock; scalar_t__ opened; int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_MIDI_EVENT_BUF ; 
 int PERM_READ ; 
 int PERM_WRITE ; 
 int SNDRV_SEQ_OSS_MAX_MIDI_DEVS ; 
 int SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC ; 
 struct seq_oss_midi* find_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct seq_oss_midi*) ; 
 struct seq_oss_midi* kzalloc (int,int /*<<< orphan*/ ) ; 
 int max_midi_devs ; 
 struct seq_oss_midi** midi_devs ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  register_lock ; 
 int /*<<< orphan*/  snd_midi_event_free (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_midi_event_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_midi_event_no_status (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_use_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_use_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
snd_seq_oss_midi_check_new_port(struct snd_seq_port_info *pinfo)
{
	int i;
	struct seq_oss_midi *mdev;
	unsigned long flags;

	/* the port must include generic midi */
	if (! (pinfo->type & SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC))
		return 0;
	/* either read or write subscribable */
	if ((pinfo->capability & PERM_WRITE) != PERM_WRITE &&
	    (pinfo->capability & PERM_READ) != PERM_READ)
		return 0;

	/*
	 * look for the identical slot
	 */
	if ((mdev = find_slot(pinfo->addr.client, pinfo->addr.port)) != NULL) {
		/* already exists */
		snd_use_lock_free(&mdev->use_lock);
		return 0;
	}

	/*
	 * allocate midi info record
	 */
	mdev = kzalloc(sizeof(*mdev), GFP_KERNEL);
	if (!mdev)
		return -ENOMEM;

	/* copy the port information */
	mdev->client = pinfo->addr.client;
	mdev->port = pinfo->addr.port;
	mdev->flags = pinfo->capability;
	mdev->opened = 0;
	snd_use_lock_init(&mdev->use_lock);

	/* copy and truncate the name of synth device */
	strlcpy(mdev->name, pinfo->name, sizeof(mdev->name));

	/* create MIDI coder */
	if (snd_midi_event_new(MAX_MIDI_EVENT_BUF, &mdev->coder) < 0) {
		pr_err("ALSA: seq_oss: can't malloc midi coder\n");
		kfree(mdev);
		return -ENOMEM;
	}
	/* OSS sequencer adds running status to all sequences */
	snd_midi_event_no_status(mdev->coder, 1);

	/*
	 * look for en empty slot
	 */
	spin_lock_irqsave(&register_lock, flags);
	for (i = 0; i < max_midi_devs; i++) {
		if (midi_devs[i] == NULL)
			break;
	}
	if (i >= max_midi_devs) {
		if (max_midi_devs >= SNDRV_SEQ_OSS_MAX_MIDI_DEVS) {
			spin_unlock_irqrestore(&register_lock, flags);
			snd_midi_event_free(mdev->coder);
			kfree(mdev);
			return -ENOMEM;
		}
		max_midi_devs++;
	}
	mdev->seq_device = i;
	midi_devs[mdev->seq_device] = mdev;
	spin_unlock_irqrestore(&register_lock, flags);

	return 0;
}