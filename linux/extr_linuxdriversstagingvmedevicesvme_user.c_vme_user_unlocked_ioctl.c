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
struct inode {int /*<<< orphan*/  i_rdev; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 unsigned int MINOR (int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 TYPE_1__* image ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vme_user_ioctl (struct inode*,struct file*,unsigned int,unsigned long) ; 

__attribute__((used)) static long
vme_user_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret;
	struct inode *inode = file_inode(file);
	unsigned int minor = MINOR(inode->i_rdev);

	mutex_lock(&image[minor].mutex);
	ret = vme_user_ioctl(inode, file, cmd, arg);
	mutex_unlock(&image[minor].mutex);

	return ret;
}