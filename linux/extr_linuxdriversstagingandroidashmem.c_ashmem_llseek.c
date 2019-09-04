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
struct file {int /*<<< orphan*/  f_pos; struct ashmem_area* private_data; } ;
struct ashmem_area {scalar_t__ size; TYPE_1__* file; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  f_pos; } ;

/* Variables and functions */
 scalar_t__ EBADF ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  ashmem_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vfs_llseek (TYPE_1__*,scalar_t__,int) ; 

__attribute__((used)) static loff_t ashmem_llseek(struct file *file, loff_t offset, int origin)
{
	struct ashmem_area *asma = file->private_data;
	loff_t ret;

	mutex_lock(&ashmem_mutex);

	if (asma->size == 0) {
		mutex_unlock(&ashmem_mutex);
		return -EINVAL;
	}

	if (!asma->file) {
		mutex_unlock(&ashmem_mutex);
		return -EBADF;
	}

	mutex_unlock(&ashmem_mutex);

	ret = vfs_llseek(asma->file, offset, origin);
	if (ret < 0)
		return ret;

	/** Copy f_pos from backing file, since f_ops->llseek() sets it */
	file->f_pos = asma->file->f_pos;
	return ret;
}