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
struct ext4_iloc {struct buffer_head* bh; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int ext4_get_inode_loc (struct inode*,struct ext4_iloc*) ; 
 int /*<<< orphan*/  ext4_std_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_write_inline_data (struct inode*,struct ext4_iloc*,void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ext4_write_lock_xattr (struct inode*,int*) ; 
 int /*<<< orphan*/  ext4_write_unlock_xattr (struct inode*,int*) ; 
 void* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 

struct buffer_head *
ext4_journalled_write_inline_data(struct inode *inode,
				  unsigned len,
				  struct page *page)
{
	int ret, no_expand;
	void *kaddr;
	struct ext4_iloc iloc;

	ret = ext4_get_inode_loc(inode, &iloc);
	if (ret) {
		ext4_std_error(inode->i_sb, ret);
		return NULL;
	}

	ext4_write_lock_xattr(inode, &no_expand);
	kaddr = kmap_atomic(page);
	ext4_write_inline_data(inode, &iloc, kaddr, 0, len);
	kunmap_atomic(kaddr);
	ext4_write_unlock_xattr(inode, &no_expand);

	return iloc.bh;
}