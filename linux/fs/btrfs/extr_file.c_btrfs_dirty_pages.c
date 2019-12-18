#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u64 ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct extent_state {int dummy; } ;
struct btrfs_fs_info {scalar_t__ sectorsize; } ;
typedef  size_t loff_t ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  io_tree; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int BTRFS_INODE_PREALLOC ; 
 int /*<<< orphan*/  ClearPageChecked (struct page*) ; 
 int EXTENT_DEFRAG ; 
 int EXTENT_DELALLOC ; 
 unsigned int EXTENT_DELALLOC_NEW ; 
 int EXTENT_DO_ACCOUNTING ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int btrfs_find_new_delalloc_bytes (TYPE_1__*,size_t,size_t,struct extent_state**) ; 
 int /*<<< orphan*/  btrfs_is_free_space_inode (TYPE_1__*) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int btrfs_set_extent_delalloc (struct inode*,size_t,size_t,unsigned int,struct extent_state**) ; 
 int /*<<< orphan*/  clear_extent_bit (int /*<<< orphan*/ *,size_t,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct extent_state**) ; 
 size_t i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,size_t) ; 
 size_t round_up (size_t,scalar_t__) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

int btrfs_dirty_pages(struct inode *inode, struct page **pages,
		      size_t num_pages, loff_t pos, size_t write_bytes,
		      struct extent_state **cached)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	int err = 0;
	int i;
	u64 num_bytes;
	u64 start_pos;
	u64 end_of_last_block;
	u64 end_pos = pos + write_bytes;
	loff_t isize = i_size_read(inode);
	unsigned int extra_bits = 0;

	start_pos = pos & ~((u64) fs_info->sectorsize - 1);
	num_bytes = round_up(write_bytes + pos - start_pos,
			     fs_info->sectorsize);

	end_of_last_block = start_pos + num_bytes - 1;

	/*
	 * The pages may have already been dirty, clear out old accounting so
	 * we can set things up properly
	 */
	clear_extent_bit(&BTRFS_I(inode)->io_tree, start_pos, end_of_last_block,
			 EXTENT_DELALLOC | EXTENT_DO_ACCOUNTING | EXTENT_DEFRAG,
			 0, 0, cached);

	if (!btrfs_is_free_space_inode(BTRFS_I(inode))) {
		if (start_pos >= isize &&
		    !(BTRFS_I(inode)->flags & BTRFS_INODE_PREALLOC)) {
			/*
			 * There can't be any extents following eof in this case
			 * so just set the delalloc new bit for the range
			 * directly.
			 */
			extra_bits |= EXTENT_DELALLOC_NEW;
		} else {
			err = btrfs_find_new_delalloc_bytes(BTRFS_I(inode),
							    start_pos,
							    num_bytes, cached);
			if (err)
				return err;
		}
	}

	err = btrfs_set_extent_delalloc(inode, start_pos, end_of_last_block,
					extra_bits, cached);
	if (err)
		return err;

	for (i = 0; i < num_pages; i++) {
		struct page *p = pages[i];
		SetPageUptodate(p);
		ClearPageChecked(p);
		set_page_dirty(p);
	}

	/*
	 * we've only changed i_size in ram, and we haven't updated
	 * the disk i_size.  There is no need to log the inode
	 * at this time.
	 */
	if (end_pos > isize)
		i_size_write(inode, end_pos);
	return 0;
}