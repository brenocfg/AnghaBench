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
struct inode {int /*<<< orphan*/  i_lock; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  i_size ;

/* Variables and functions */
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void v9fs_i_size_write(struct inode *inode, loff_t i_size)
{
	/*
	 * 32-bit need the lock, concurrent updates could break the
	 * sequences and make i_size_read() loop forever.
	 * 64-bit updates are atomic and can skip the locking.
	 */
	if (sizeof(i_size) > sizeof(long))
		spin_lock(&inode->i_lock);
	i_size_write(inode, i_size);
	if (sizeof(i_size) > sizeof(long))
		spin_unlock(&inode->i_lock);
}