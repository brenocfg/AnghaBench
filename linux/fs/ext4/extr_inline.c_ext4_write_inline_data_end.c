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
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_iloc {int /*<<< orphan*/  bh; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ClearPageDirty (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int ext4_get_inode_loc (struct inode*,struct ext4_iloc*) ; 
 int /*<<< orphan*/  ext4_has_inline_data (struct inode*) ; 
 int /*<<< orphan*/  ext4_std_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_write_inline_data (struct inode*,struct ext4_iloc*,void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ext4_write_lock_xattr (struct inode*,int*) ; 
 int /*<<< orphan*/  ext4_write_unlock_xattr (struct inode*,int*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 scalar_t__ unlikely (int) ; 

int ext4_write_inline_data_end(struct inode *inode, loff_t pos, unsigned len,
			       unsigned copied, struct page *page)
{
	int ret, no_expand;
	void *kaddr;
	struct ext4_iloc iloc;

	if (unlikely(copied < len)) {
		if (!PageUptodate(page)) {
			copied = 0;
			goto out;
		}
	}

	ret = ext4_get_inode_loc(inode, &iloc);
	if (ret) {
		ext4_std_error(inode->i_sb, ret);
		copied = 0;
		goto out;
	}

	ext4_write_lock_xattr(inode, &no_expand);
	BUG_ON(!ext4_has_inline_data(inode));

	kaddr = kmap_atomic(page);
	ext4_write_inline_data(inode, &iloc, kaddr, pos, len);
	kunmap_atomic(kaddr);
	SetPageUptodate(page);
	/* clear page dirty so that writepages wouldn't work for us. */
	ClearPageDirty(page);

	ext4_write_unlock_xattr(inode, &no_expand);
	brelse(iloc.bh);
	mark_inode_dirty(inode);
out:
	return copied;
}