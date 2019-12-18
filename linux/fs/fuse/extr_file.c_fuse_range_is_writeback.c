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
struct inode {int dummy; } ;
struct fuse_inode {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int fuse_find_writeback (struct fuse_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool fuse_range_is_writeback(struct inode *inode, pgoff_t idx_from,
				   pgoff_t idx_to)
{
	struct fuse_inode *fi = get_fuse_inode(inode);
	bool found;

	spin_lock(&fi->lock);
	found = fuse_find_writeback(fi, idx_from, idx_to);
	spin_unlock(&fi->lock);

	return found;
}