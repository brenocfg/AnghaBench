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
 int megadev_ioctl (struct file*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  megadev_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long
megadev_unlocked_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
	int ret;

	mutex_lock(&megadev_mutex);
	ret = megadev_ioctl(filep, cmd, arg);
	mutex_unlock(&megadev_mutex);

	return ret;
}