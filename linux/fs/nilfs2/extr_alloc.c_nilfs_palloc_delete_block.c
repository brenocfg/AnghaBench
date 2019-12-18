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
struct nilfs_bh_assoc {unsigned long blkoff; int /*<<< orphan*/ * bh; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int nilfs_mdt_delete_block (struct inode*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_palloc_delete_block(struct inode *inode, unsigned long blkoff,
				     struct nilfs_bh_assoc *prev,
				     spinlock_t *lock)
{
	spin_lock(lock);
	if (prev->bh && blkoff == prev->blkoff) {
		brelse(prev->bh);
		prev->bh = NULL;
	}
	spin_unlock(lock);
	return nilfs_mdt_delete_block(inode, blkoff);
}