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
typedef  int /*<<< orphan*/  subs ;
struct TYPE_2__ {int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct snd_seq_port_subscribe {int /*<<< orphan*/  queue; int /*<<< orphan*/  flags; TYPE_1__ dest; TYPE_1__ sender; } ;
struct seq_oss_midi {int opened; int flags; int /*<<< orphan*/  use_lock; struct seq_oss_devinfo* devinfo; int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct seq_oss_devinfo {int /*<<< orphan*/  cseq; int /*<<< orphan*/  queue; TYPE_1__ addr; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENXIO ; 
 int PERM_READ ; 
 int PERM_WRITE ; 
 int /*<<< orphan*/  SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT ; 
 int /*<<< orphan*/  SNDRV_SEQ_PORT_SUBS_TIMESTAMP ; 
 struct seq_oss_midi* get_mididev (struct seq_oss_devinfo*,int) ; 
 scalar_t__ is_read_mode (int) ; 
 scalar_t__ is_write_mode (int) ; 
 int /*<<< orphan*/  memset (struct snd_seq_port_subscribe*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snd_seq_kernel_client_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_seq_port_subscribe*) ; 
 int /*<<< orphan*/  snd_use_lock_free (int /*<<< orphan*/ *) ; 

int
snd_seq_oss_midi_open(struct seq_oss_devinfo *dp, int dev, int fmode)
{
	int perm;
	struct seq_oss_midi *mdev;
	struct snd_seq_port_subscribe subs;

	if ((mdev = get_mididev(dp, dev)) == NULL)
		return -ENODEV;

	/* already used? */
	if (mdev->opened && mdev->devinfo != dp) {
		snd_use_lock_free(&mdev->use_lock);
		return -EBUSY;
	}

	perm = 0;
	if (is_write_mode(fmode))
		perm |= PERM_WRITE;
	if (is_read_mode(fmode))
		perm |= PERM_READ;
	perm &= mdev->flags;
	if (perm == 0) {
		snd_use_lock_free(&mdev->use_lock);
		return -ENXIO;
	}

	/* already opened? */
	if ((mdev->opened & perm) == perm) {
		snd_use_lock_free(&mdev->use_lock);
		return 0;
	}

	perm &= ~mdev->opened;

	memset(&subs, 0, sizeof(subs));

	if (perm & PERM_WRITE) {
		subs.sender = dp->addr;
		subs.dest.client = mdev->client;
		subs.dest.port = mdev->port;
		if (snd_seq_kernel_client_ctl(dp->cseq, SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT, &subs) >= 0)
			mdev->opened |= PERM_WRITE;
	}
	if (perm & PERM_READ) {
		subs.sender.client = mdev->client;
		subs.sender.port = mdev->port;
		subs.dest = dp->addr;
		subs.flags = SNDRV_SEQ_PORT_SUBS_TIMESTAMP;
		subs.queue = dp->queue;		/* queue for timestamps */
		if (snd_seq_kernel_client_ctl(dp->cseq, SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT, &subs) >= 0)
			mdev->opened |= PERM_READ;
	}

	if (! mdev->opened) {
		snd_use_lock_free(&mdev->use_lock);
		return -ENXIO;
	}

	mdev->devinfo = dp;
	snd_use_lock_free(&mdev->use_lock);
	return 0;
}