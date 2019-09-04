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
struct inode {int /*<<< orphan*/  i_sb; } ;
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
 int ext4_da_convert_inline_data_to_extent (struct address_space*,struct inode*,unsigned int,void**) ; 
 int ext4_get_inode_loc (struct inode*,struct ext4_iloc*) ; 
 int ext4_get_max_inline_size (struct inode*) ; 
 int /*<<< orphan*/  ext4_has_inline_data (struct inode*) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int ext4_prepare_inline_data (int /*<<< orphan*/ *,struct inode*,unsigned int) ; 
 int ext4_read_inline_page (struct inode*,struct page*) ; 
 scalar_t__ ext4_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int ext4_da_write_inline_data_begin(struct address_space *mapping,
				    struct inode *inode,
				    loff_t pos, unsigned len,
				    unsigned flags,
				    struct page **pagep,
				    void **fsdata)
{
	int ret, inline_size;
	handle_t *handle;
	struct page *page;
	struct ext4_iloc iloc;
	int retries = 0;

	ret = ext4_get_inode_loc(inode, &iloc);
	if (ret)
		return ret;

retry_journal:
	handle = ext4_journal_start(inode, EXT4_HT_INODE, 1);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		goto out;
	}

	inline_size = ext4_get_max_inline_size(inode);

	ret = -ENOSPC;
	if (inline_size >= pos + len) {
		ret = ext4_prepare_inline_data(handle, inode, pos + len);
		if (ret && ret != -ENOSPC)
			goto out_journal;
	}

	/*
	 * We cannot recurse into the filesystem as the transaction
	 * is already started.
	 */
	flags |= AOP_FLAG_NOFS;

	if (ret == -ENOSPC) {
		ext4_journal_stop(handle);
		ret = ext4_da_convert_inline_data_to_extent(mapping,
							    inode,
							    flags,
							    fsdata);
		if (ret == -ENOSPC &&
		    ext4_should_retry_alloc(inode->i_sb, &retries))
			goto retry_journal;
		goto out;
	}

	page = grab_cache_page_write_begin(mapping, 0, flags);
	if (!page) {
		ret = -ENOMEM;
		goto out_journal;
	}

	down_read(&EXT4_I(inode)->xattr_sem);
	if (!ext4_has_inline_data(inode)) {
		ret = 0;
		goto out_release_page;
	}

	if (!PageUptodate(page)) {
		ret = ext4_read_inline_page(inode, page);
		if (ret < 0)
			goto out_release_page;
	}
	ret = ext4_journal_get_write_access(handle, iloc.bh);
	if (ret)
		goto out_release_page;

	up_read(&EXT4_I(inode)->xattr_sem);
	*pagep = page;
	brelse(iloc.bh);
	return 1;
out_release_page:
	up_read(&EXT4_I(inode)->xattr_sem);
	unlock_page(page);
	put_page(page);
out_journal:
	ext4_journal_stop(handle);
out:
	brelse(iloc.bh);
	return ret;
}