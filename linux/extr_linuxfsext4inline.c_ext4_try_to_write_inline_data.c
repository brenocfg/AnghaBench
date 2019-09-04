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
struct ext4_iloc {int /*<<< orphan*/  bh; } ;
struct address_space {int dummy; } ;
typedef  unsigned int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  xattr_sem; } ;

/* Variables and functions */
 unsigned int AOP_FLAG_NOFS ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  EXT4_HT_INODE ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int ext4_convert_inline_data_to_extent (struct address_space*,struct inode*,unsigned int) ; 
 int ext4_get_inode_loc (struct inode*,struct ext4_iloc*) ; 
 unsigned int ext4_get_max_inline_size (struct inode*) ; 
 int /*<<< orphan*/  ext4_has_inline_data (struct inode*) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int ext4_prepare_inline_data (int /*<<< orphan*/ *,struct inode*,unsigned int) ; 
 int ext4_read_inline_page (struct inode*,struct page*) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int ext4_try_to_write_inline_data(struct address_space *mapping,
				  struct inode *inode,
				  loff_t pos, unsigned len,
				  unsigned flags,
				  struct page **pagep)
{
	int ret;
	handle_t *handle;
	struct page *page;
	struct ext4_iloc iloc;

	if (pos + len > ext4_get_max_inline_size(inode))
		goto convert;

	ret = ext4_get_inode_loc(inode, &iloc);
	if (ret)
		return ret;

	/*
	 * The possible write could happen in the inode,
	 * so try to reserve the space in inode first.
	 */
	handle = ext4_journal_start(inode, EXT4_HT_INODE, 1);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		handle = NULL;
		goto out;
	}

	ret = ext4_prepare_inline_data(handle, inode, pos + len);
	if (ret && ret != -ENOSPC)
		goto out;

	/* We don't have space in inline inode, so convert it to extent. */
	if (ret == -ENOSPC) {
		ext4_journal_stop(handle);
		brelse(iloc.bh);
		goto convert;
	}

	ret = ext4_journal_get_write_access(handle, iloc.bh);
	if (ret)
		goto out;

	flags |= AOP_FLAG_NOFS;

	page = grab_cache_page_write_begin(mapping, 0, flags);
	if (!page) {
		ret = -ENOMEM;
		goto out;
	}

	*pagep = page;
	down_read(&EXT4_I(inode)->xattr_sem);
	if (!ext4_has_inline_data(inode)) {
		ret = 0;
		unlock_page(page);
		put_page(page);
		goto out_up_read;
	}

	if (!PageUptodate(page)) {
		ret = ext4_read_inline_page(inode, page);
		if (ret < 0) {
			unlock_page(page);
			put_page(page);
			goto out_up_read;
		}
	}

	ret = 1;
	handle = NULL;
out_up_read:
	up_read(&EXT4_I(inode)->xattr_sem);
out:
	if (handle && (ret != 1))
		ext4_journal_stop(handle);
	brelse(iloc.bh);
	return ret;
convert:
	return ext4_convert_inline_data_to_extent(mapping,
						  inode, flags);
}