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
struct page {scalar_t__ index; } ;
struct ocfs2_inode_info {int ip_dyn_features; int /*<<< orphan*/  ip_alloc_sem; } ;
struct list_head {int dummy; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EIO ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 int /*<<< orphan*/  OCFS2_LOCK_NONBLOCK ; 
 int PAGE_SHIFT ; 
 scalar_t__ down_read_trylock (int /*<<< orphan*/ *) ; 
 int i_size_read (struct inode*) ; 
 struct page* lru_to_page (struct list_head*) ; 
 int mpage_readpages (struct address_space*,struct list_head*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_get_block ; 
 int ocfs2_inode_lock_full (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_readpages(struct file *filp, struct address_space *mapping,
			   struct list_head *pages, unsigned nr_pages)
{
	int ret, err = -EIO;
	struct inode *inode = mapping->host;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	loff_t start;
	struct page *last;

	/*
	 * Use the nonblocking flag for the dlm code to avoid page
	 * lock inversion, but don't bother with retrying.
	 */
	ret = ocfs2_inode_lock_full(inode, NULL, 0, OCFS2_LOCK_NONBLOCK);
	if (ret)
		return err;

	if (down_read_trylock(&oi->ip_alloc_sem) == 0) {
		ocfs2_inode_unlock(inode, 0);
		return err;
	}

	/*
	 * Don't bother with inline-data. There isn't anything
	 * to read-ahead in that case anyway...
	 */
	if (oi->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		goto out_unlock;

	/*
	 * Check whether a remote node truncated this file - we just
	 * drop out in that case as it's not worth handling here.
	 */
	last = lru_to_page(pages);
	start = (loff_t)last->index << PAGE_SHIFT;
	if (start >= i_size_read(inode))
		goto out_unlock;

	err = mpage_readpages(mapping, pages, nr_pages, ocfs2_get_block);

out_unlock:
	up_read(&oi->ip_alloc_sem);
	ocfs2_inode_unlock(inode, 0);

	return err;
}