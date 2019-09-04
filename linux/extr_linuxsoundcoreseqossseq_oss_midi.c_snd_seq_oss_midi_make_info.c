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
struct seq_oss_midi {int /*<<< orphan*/  use_lock; int /*<<< orphan*/  name; } ;
struct seq_oss_devinfo {int dummy; } ;
struct midi_info {int device; int /*<<< orphan*/  name; scalar_t__ capabilities; scalar_t__ dev_type; } ;

/* Variables and functions */
 int ENXIO ; 
 struct seq_oss_midi* get_mididev (struct seq_oss_devinfo*,int) ; 
 int /*<<< orphan*/  snd_use_lock_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
snd_seq_oss_midi_make_info(struct seq_oss_devinfo *dp, int dev, struct midi_info *inf)
{
	struct seq_oss_midi *mdev;

	if ((mdev = get_mididev(dp, dev)) == NULL)
		return -ENXIO;
	inf->device = dev;
	inf->dev_type = 0; /* FIXME: ?? */
	inf->capabilities = 0; /* FIXME: ?? */
	strlcpy(inf->name, mdev->name, sizeof(inf->name));
	snd_use_lock_free(&mdev->use_lock);
	return 0;
}