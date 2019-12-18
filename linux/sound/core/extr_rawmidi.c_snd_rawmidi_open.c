#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_entry_t ;
struct snd_rawmidi_file {TYPE_4__* output; TYPE_2__* input; } ;
struct snd_rawmidi {struct snd_card* card; int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  open_wait; } ;
struct snd_card {int /*<<< orphan*/  module; scalar_t__ shutdown; } ;
struct inode {int dummy; } ;
struct file {int f_flags; struct snd_rawmidi_file* private_data; } ;
struct TYPE_8__ {TYPE_3__* runtime; } ;
struct TYPE_7__ {int oss; } ;
struct TYPE_6__ {TYPE_1__* runtime; } ;
struct TYPE_5__ {int oss; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int O_APPEND ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SNDRV_DEVICE_TYPE_RAWMIDI ; 
 int /*<<< orphan*/  SNDRV_OSS_DEVICE_TYPE_MIDI ; 
 unsigned short SNDRV_RAWMIDI_LFLG_APPEND ; 
 int /*<<< orphan*/  SND_CTL_SUBDEV_RAWMIDI ; 
 int SOUND_MAJOR ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int imajor (struct inode*) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_rawmidi_file*) ; 
 struct snd_rawmidi_file* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rawmidi_open_priv (struct snd_rawmidi*,int,unsigned short,struct snd_rawmidi_file*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int snd_card_file_add (struct snd_card*,struct file*) ; 
 int /*<<< orphan*/  snd_card_file_remove (struct snd_card*,struct file*) ; 
 int /*<<< orphan*/  snd_card_unref (struct snd_card*) ; 
 int snd_ctl_get_preferred_subdevice (struct snd_card*,int /*<<< orphan*/ ) ; 
 struct snd_rawmidi* snd_lookup_minor_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_rawmidi* snd_lookup_oss_minor_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_major ; 
 unsigned short snd_rawmidi_file_flags (struct file*) ; 
 int stream_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_rawmidi_open(struct inode *inode, struct file *file)
{
	int maj = imajor(inode);
	struct snd_card *card;
	int subdevice;
	unsigned short fflags;
	int err;
	struct snd_rawmidi *rmidi;
	struct snd_rawmidi_file *rawmidi_file = NULL;
	wait_queue_entry_t wait;

	if ((file->f_flags & O_APPEND) && !(file->f_flags & O_NONBLOCK))
		return -EINVAL;		/* invalid combination */

	err = stream_open(inode, file);
	if (err < 0)
		return err;

	if (maj == snd_major) {
		rmidi = snd_lookup_minor_data(iminor(inode),
					      SNDRV_DEVICE_TYPE_RAWMIDI);
#ifdef CONFIG_SND_OSSEMUL
	} else if (maj == SOUND_MAJOR) {
		rmidi = snd_lookup_oss_minor_data(iminor(inode),
						  SNDRV_OSS_DEVICE_TYPE_MIDI);
#endif
	} else
		return -ENXIO;

	if (rmidi == NULL)
		return -ENODEV;

	if (!try_module_get(rmidi->card->module)) {
		snd_card_unref(rmidi->card);
		return -ENXIO;
	}

	mutex_lock(&rmidi->open_mutex);
	card = rmidi->card;
	err = snd_card_file_add(card, file);
	if (err < 0)
		goto __error_card;
	fflags = snd_rawmidi_file_flags(file);
	if ((file->f_flags & O_APPEND) || maj == SOUND_MAJOR) /* OSS emul? */
		fflags |= SNDRV_RAWMIDI_LFLG_APPEND;
	rawmidi_file = kmalloc(sizeof(*rawmidi_file), GFP_KERNEL);
	if (rawmidi_file == NULL) {
		err = -ENOMEM;
		goto __error;
	}
	init_waitqueue_entry(&wait, current);
	add_wait_queue(&rmidi->open_wait, &wait);
	while (1) {
		subdevice = snd_ctl_get_preferred_subdevice(card, SND_CTL_SUBDEV_RAWMIDI);
		err = rawmidi_open_priv(rmidi, subdevice, fflags, rawmidi_file);
		if (err >= 0)
			break;
		if (err == -EAGAIN) {
			if (file->f_flags & O_NONBLOCK) {
				err = -EBUSY;
				break;
			}
		} else
			break;
		set_current_state(TASK_INTERRUPTIBLE);
		mutex_unlock(&rmidi->open_mutex);
		schedule();
		mutex_lock(&rmidi->open_mutex);
		if (rmidi->card->shutdown) {
			err = -ENODEV;
			break;
		}
		if (signal_pending(current)) {
			err = -ERESTARTSYS;
			break;
		}
	}
	remove_wait_queue(&rmidi->open_wait, &wait);
	if (err < 0) {
		kfree(rawmidi_file);
		goto __error;
	}
#ifdef CONFIG_SND_OSSEMUL
	if (rawmidi_file->input && rawmidi_file->input->runtime)
		rawmidi_file->input->runtime->oss = (maj == SOUND_MAJOR);
	if (rawmidi_file->output && rawmidi_file->output->runtime)
		rawmidi_file->output->runtime->oss = (maj == SOUND_MAJOR);
#endif
	file->private_data = rawmidi_file;
	mutex_unlock(&rmidi->open_mutex);
	snd_card_unref(rmidi->card);
	return 0;

 __error:
	snd_card_file_remove(card, file);
 __error_card:
	mutex_unlock(&rmidi->open_mutex);
	module_put(rmidi->card->module);
	snd_card_unref(rmidi->card);
	return err;
}