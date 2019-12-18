#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_entry_t ;
struct TYPE_4__ {int (* open ) (struct snd_hwdep*,struct file*) ;int /*<<< orphan*/  (* release ) (struct snd_hwdep*,struct file*) ;} ;
struct snd_hwdep {scalar_t__ used; TYPE_2__* card; int /*<<< orphan*/  open_mutex; TYPE_1__ ops; int /*<<< orphan*/  open_wait; scalar_t__ exclusive; } ;
struct inode {int dummy; } ;
struct file {int f_flags; struct snd_hwdep* private_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  module; scalar_t__ shutdown; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EFAULT ; 
 int ENODEV ; 
 int ENXIO ; 
 int ERESTARTSYS ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SNDRV_DEVICE_TYPE_HWDEP ; 
 int /*<<< orphan*/  SNDRV_OSS_DEVICE_TYPE_DMFM ; 
 int SOUND_MAJOR ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int imajor (struct inode*) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int snd_card_file_add (TYPE_2__*,struct file*) ; 
 int /*<<< orphan*/  snd_card_unref (TYPE_2__*) ; 
 struct snd_hwdep* snd_lookup_minor_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_hwdep* snd_lookup_oss_minor_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_major ; 
 int stub1 (struct snd_hwdep*,struct file*) ; 
 int /*<<< orphan*/  stub2 (struct snd_hwdep*,struct file*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_hwdep_open(struct inode *inode, struct file * file)
{
	int major = imajor(inode);
	struct snd_hwdep *hw;
	int err;
	wait_queue_entry_t wait;

	if (major == snd_major) {
		hw = snd_lookup_minor_data(iminor(inode),
					   SNDRV_DEVICE_TYPE_HWDEP);
#ifdef CONFIG_SND_OSSEMUL
	} else if (major == SOUND_MAJOR) {
		hw = snd_lookup_oss_minor_data(iminor(inode),
					       SNDRV_OSS_DEVICE_TYPE_DMFM);
#endif
	} else
		return -ENXIO;
	if (hw == NULL)
		return -ENODEV;

	if (!try_module_get(hw->card->module)) {
		snd_card_unref(hw->card);
		return -EFAULT;
	}

	init_waitqueue_entry(&wait, current);
	add_wait_queue(&hw->open_wait, &wait);
	mutex_lock(&hw->open_mutex);
	while (1) {
		if (hw->exclusive && hw->used > 0) {
			err = -EBUSY;
			break;
		}
		if (!hw->ops.open) {
			err = 0;
			break;
		}
		err = hw->ops.open(hw, file);
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
		mutex_unlock(&hw->open_mutex);
		schedule();
		mutex_lock(&hw->open_mutex);
		if (hw->card->shutdown) {
			err = -ENODEV;
			break;
		}
		if (signal_pending(current)) {
			err = -ERESTARTSYS;
			break;
		}
	}
	remove_wait_queue(&hw->open_wait, &wait);
	if (err >= 0) {
		err = snd_card_file_add(hw->card, file);
		if (err >= 0) {
			file->private_data = hw;
			hw->used++;
		} else {
			if (hw->ops.release)
				hw->ops.release(hw, file);
		}
	}
	mutex_unlock(&hw->open_mutex);
	if (err < 0)
		module_put(hw->card->module);
	snd_card_unref(hw->card);
	return err;
}