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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct address_space {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  xattr_sem; } ;

/* Variables and functions */
 scalar_t__ CONVERT_INLINE_DATA ; 
 int ENOMEM ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_STATE_MAY_INLINE_DATA ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int __block_write_begin (struct page*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_clear_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_da_get_block_prep ; 
 int ext4_get_inline_size (struct inode*) ; 
 int /*<<< orphan*/  ext4_has_inline_data (struct inode*) ; 
 int ext4_read_inline_page (struct inode*,struct page*) ; 
 int /*<<< orphan*/  ext4_truncate_failed_write (struct inode*) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext4_da_convert_inline_data_to_extent(struct address_space *mapping,
						 struct inode *inode,
						 unsigned flags,
						 void **fsdata)
{
	int ret = 0, inline_size;
	struct page *page;

	page = grab_cache_page_write_begin(mapping, 0, flags);
	if (!page)
		return -ENOMEM;

	down_read(&EXT4_I(inode)->xattr_sem);
	if (!ext4_has_inline_data(inode)) {
		ext4_clear_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
		goto out;
	}

	inline_size = ext4_get_inline_size(inode);

	if (!PageUptodate(page)) {
		ret = ext4_read_inline_page(inode, page);
		if (ret < 0)
			goto out;
	}

	ret = __block_write_begin(page, 0, inline_size,
				  ext4_da_get_block_prep);
	if (ret) {
		up_read(&EXT4_I(inode)->xattr_sem);
		unlock_page(page);
		put_page(page);
		ext4_truncate_failed_write(inode);
		return ret;
	}

	SetPageDirty(page);
	SetPageUptodate(page);
	ext4_clear_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
	*fsdata = (void *)CONVERT_INLINE_DATA;

out:
	up_read(&EXT4_I(inode)->xattr_sem);
	if (page) {
		unlock_page(page);
		put_page(page);
	}
	return ret;
}