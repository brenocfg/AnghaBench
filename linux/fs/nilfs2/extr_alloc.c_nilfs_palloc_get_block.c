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
struct nilfs_bh_assoc {unsigned long blkoff; struct buffer_head* bh; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int nilfs_mdt_get_block (struct inode*,unsigned long,int,void (*) (struct inode*,struct buffer_head*,void*),struct buffer_head**) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_palloc_get_block(struct inode *inode, unsigned long blkoff,
				  int create,
				  void (*init_block)(struct inode *,
						     struct buffer_head *,
						     void *),
				  struct buffer_head **bhp,
				  struct nilfs_bh_assoc *prev,
				  spinlock_t *lock)
{
	int ret;

	spin_lock(lock);
	if (prev->bh && blkoff == prev->blkoff) {
		get_bh(prev->bh);
		*bhp = prev->bh;
		spin_unlock(lock);
		return 0;
	}
	spin_unlock(lock);

	ret = nilfs_mdt_get_block(inode, blkoff, create, init_block, bhp);
	if (!ret) {
		spin_lock(lock);
		/*
		 * The following code must be safe for change of the
		 * cache contents during the get block call.
		 */
		brelse(prev->bh);
		get_bh(*bhp);
		prev->bh = *bhp;
		prev->blkoff = blkoff;
		spin_unlock(lock);
	}
	return ret;
}