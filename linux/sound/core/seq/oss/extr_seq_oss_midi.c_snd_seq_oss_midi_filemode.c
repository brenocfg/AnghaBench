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
struct seq_oss_midi {int opened; int /*<<< orphan*/  use_lock; } ;
struct seq_oss_devinfo {int dummy; } ;

/* Variables and functions */
 int PERM_READ ; 
 int PERM_WRITE ; 
 int SNDRV_SEQ_OSS_FILE_READ ; 
 int SNDRV_SEQ_OSS_FILE_WRITE ; 
 struct seq_oss_midi* get_mididev (struct seq_oss_devinfo*,int) ; 
 int /*<<< orphan*/  snd_use_lock_free (int /*<<< orphan*/ *) ; 

int
snd_seq_oss_midi_filemode(struct seq_oss_devinfo *dp, int dev)
{
	struct seq_oss_midi *mdev;
	int mode;

	if ((mdev = get_mididev(dp, dev)) == NULL)
		return 0;

	mode = 0;
	if (mdev->opened & PERM_WRITE)
		mode |= SNDRV_SEQ_OSS_FILE_WRITE;
	if (mdev->opened & PERM_READ)
		mode |= SNDRV_SEQ_OSS_FILE_READ;

	snd_use_lock_free(&mdev->use_lock);
	return mode;
}