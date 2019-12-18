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
struct kcov {int /*<<< orphan*/  lock; } ;
struct file {struct kcov* private_data; } ;

/* Variables and functions */
 int kcov_ioctl_locked (struct kcov*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long kcov_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
	struct kcov *kcov;
	int res;

	kcov = filep->private_data;
	spin_lock(&kcov->lock);
	res = kcov_ioctl_locked(kcov, cmd, arg);
	spin_unlock(&kcov->lock);
	return res;
}