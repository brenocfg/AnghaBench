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
struct snd_seq_port_subscribe {TYPE_1__ dest; TYPE_1__ sender; } ;
struct seq_oss_midi {int opened; int /*<<< orphan*/  use_lock; struct seq_oss_devinfo* devinfo; int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct seq_oss_devinfo {int /*<<< orphan*/  cseq; TYPE_1__ addr; } ;

/* Variables and functions */
 int ENODEV ; 
 int PERM_READ ; 
 int PERM_WRITE ; 
 int /*<<< orphan*/  SNDRV_SEQ_IOCTL_UNSUBSCRIBE_PORT ; 
 struct seq_oss_midi* get_mididev (struct seq_oss_devinfo*,int) ; 
 int /*<<< orphan*/  memset (struct snd_seq_port_subscribe*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_seq_kernel_client_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_seq_port_subscribe*) ; 
 int /*<<< orphan*/  snd_use_lock_free (int /*<<< orphan*/ *) ; 

int
snd_seq_oss_midi_close(struct seq_oss_devinfo *dp, int dev)
{
	struct seq_oss_midi *mdev;
	struct snd_seq_port_subscribe subs;

	if ((mdev = get_mididev(dp, dev)) == NULL)
		return -ENODEV;
	if (! mdev->opened || mdev->devinfo != dp) {
		snd_use_lock_free(&mdev->use_lock);
		return 0;
	}

	memset(&subs, 0, sizeof(subs));
	if (mdev->opened & PERM_WRITE) {
		subs.sender = dp->addr;
		subs.dest.client = mdev->client;
		subs.dest.port = mdev->port;
		snd_seq_kernel_client_ctl(dp->cseq, SNDRV_SEQ_IOCTL_UNSUBSCRIBE_PORT, &subs);
	}
	if (mdev->opened & PERM_READ) {
		subs.sender.client = mdev->client;
		subs.sender.port = mdev->port;
		subs.dest = dp->addr;
		snd_seq_kernel_client_ctl(dp->cseq, SNDRV_SEQ_IOCTL_UNSUBSCRIBE_PORT, &subs);
	}

	mdev->opened = 0;
	mdev->devinfo = NULL;

	snd_use_lock_free(&mdev->use_lock);
	return 0;
}