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
struct snd_timer_user {int ticks; int /*<<< orphan*/  ioctl_lock; int /*<<< orphan*/  qchange_sleep; int /*<<< orphan*/  qlock; } ;
struct inode {int dummy; } ;
struct file {struct snd_timer_user* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_timer_user*) ; 
 struct snd_timer_user* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ realloc_user_queue (struct snd_timer_user*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stream_open (struct inode*,struct file*) ; 

__attribute__((used)) static int snd_timer_user_open(struct inode *inode, struct file *file)
{
	struct snd_timer_user *tu;
	int err;

	err = stream_open(inode, file);
	if (err < 0)
		return err;

	tu = kzalloc(sizeof(*tu), GFP_KERNEL);
	if (tu == NULL)
		return -ENOMEM;
	spin_lock_init(&tu->qlock);
	init_waitqueue_head(&tu->qchange_sleep);
	mutex_init(&tu->ioctl_lock);
	tu->ticks = 1;
	if (realloc_user_queue(tu, 128) < 0) {
		kfree(tu);
		return -ENOMEM;
	}
	file->private_data = tu;
	return 0;
}