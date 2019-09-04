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
struct file {int dummy; } ;

/* Variables and functions */
 int mraid_mm_ioctl (struct file*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  mraid_mm_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long
mraid_mm_unlocked_ioctl(struct file *filep, unsigned int cmd,
		        unsigned long arg)
{
	int err;

	/* inconsistent: mraid_mm_compat_ioctl doesn't take the BKL */
	mutex_lock(&mraid_mm_mutex);
	err = mraid_mm_ioctl(filep, cmd, arg);
	mutex_unlock(&mraid_mm_mutex);

	return err;
}