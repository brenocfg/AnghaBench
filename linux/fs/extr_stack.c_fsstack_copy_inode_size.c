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
struct inode {int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_blocks; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  i_size ;
typedef  int /*<<< orphan*/  i_blocks ;
typedef  int /*<<< orphan*/  blkcnt_t ;

/* Variables and functions */
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void fsstack_copy_inode_size(struct inode *dst, struct inode *src)
{
	loff_t i_size;
	blkcnt_t i_blocks;

	/*
	 * i_size_read() includes its own seqlocking and protection from
	 * preemption (see include/linux/fs.h): we need nothing extra for
	 * that here, and prefer to avoid nesting locks than attempt to keep
	 * i_size and i_blocks in sync together.
	 */
	i_size = i_size_read(src);

	/*
	 * But on 32-bit, we ought to make an effort to keep the two halves of
	 * i_blocks in sync despite SMP or PREEMPT - though stat's
	 * generic_fillattr() doesn't bother, and we won't be applying quotas
	 * (where i_blocks does become important) at the upper level.
	 *
	 * We don't actually know what locking is used at the lower level;
	 * but if it's a filesystem that supports quotas, it will be using
	 * i_lock as in inode_add_bytes().
	 */
	if (sizeof(i_blocks) > sizeof(long))
		spin_lock(&src->i_lock);
	i_blocks = src->i_blocks;
	if (sizeof(i_blocks) > sizeof(long))
		spin_unlock(&src->i_lock);

	/*
	 * If CONFIG_SMP or CONFIG_PREEMPT on 32-bit, it's vital for
	 * fsstack_copy_inode_size() to hold some lock around
	 * i_size_write(), otherwise i_size_read() may spin forever (see
	 * include/linux/fs.h).  We don't necessarily hold i_mutex when this
	 * is called, so take i_lock for that case.
	 *
	 * And if on 32-bit, continue our effort to keep the two halves of
	 * i_blocks in sync despite SMP or PREEMPT: use i_lock  for that case
	 * too, and do both at once by combining the tests.
	 *
	 * There is none of this locking overhead in the 64-bit case.
	 */
	if (sizeof(i_size) > sizeof(long) || sizeof(i_blocks) > sizeof(long))
		spin_lock(&dst->i_lock);
	i_size_write(dst, i_size);
	dst->i_blocks = i_blocks;
	if (sizeof(i_size) > sizeof(long) || sizeof(i_blocks) > sizeof(long))
		spin_unlock(&dst->i_lock);
}