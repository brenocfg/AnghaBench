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
struct snd_timer_user {struct snd_timer_user* tqueue; struct snd_timer_user* queue; int /*<<< orphan*/  ioctl_lock; scalar_t__ timeri; } ;
struct inode {int dummy; } ;
struct file {struct snd_timer_user* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_timer_user*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_timer_close (scalar_t__) ; 

__attribute__((used)) static int snd_timer_user_release(struct inode *inode, struct file *file)
{
	struct snd_timer_user *tu;

	if (file->private_data) {
		tu = file->private_data;
		file->private_data = NULL;
		mutex_lock(&tu->ioctl_lock);
		if (tu->timeri)
			snd_timer_close(tu->timeri);
		mutex_unlock(&tu->ioctl_lock);
		kfree(tu->queue);
		kfree(tu->tqueue);
		kfree(tu);
	}
	return 0;
}