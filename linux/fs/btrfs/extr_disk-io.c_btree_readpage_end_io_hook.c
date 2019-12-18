#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct page {scalar_t__ private; TYPE_1__* mapping; } ;
struct extent_buffer {int read_mirror; scalar_t__ start; int /*<<< orphan*/  io_pages; int /*<<< orphan*/  bflags; } ;
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_io_bio {int dummy; } ;
struct btrfs_fs_info {TYPE_2__* sb; int /*<<< orphan*/  super_copy; } ;
struct TYPE_6__ {struct btrfs_root* root; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int BTRFS_CSUM_SIZE ; 
 TYPE_3__* BTRFS_I (int /*<<< orphan*/ ) ; 
 int BTRFS_MAX_LEVEL ; 
 int EIO ; 
 int EUCLEAN ; 
 int /*<<< orphan*/  EXTENT_BUFFER_CORRUPT ; 
 int /*<<< orphan*/  EXTENT_BUFFER_READAHEAD ; 
 int /*<<< orphan*/  EXTENT_BUFFER_READ_ERR ; 
 int atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btree_readahead_hook (struct extent_buffer*,int) ; 
 scalar_t__ btrfs_check_leaf_full (struct extent_buffer*) ; 
 scalar_t__ btrfs_check_node (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  btrfs_err_rl (struct btrfs_fs_info*,char*,scalar_t__,...) ; 
 scalar_t__ btrfs_header_bytenr (struct extent_buffer*) ; 
 int btrfs_header_level (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_header_owner (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_set_buffer_lockdep_class (int /*<<< orphan*/ ,struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_super_csum_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_warn_rl (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ check_tree_block_fsid (struct extent_buffer*) ; 
 int /*<<< orphan*/  clear_extent_buffer_uptodate (struct extent_buffer*) ; 
 int csum_tree_block (struct extent_buffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_buffer_get (struct extent_buffer*) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 scalar_t__ memcmp_extent_buffer (struct extent_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_extent_buffer (struct extent_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_extent_buffer_uptodate (struct extent_buffer*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btree_readpage_end_io_hook(struct btrfs_io_bio *io_bio,
				      u64 phy_offset, struct page *page,
				      u64 start, u64 end, int mirror)
{
	u64 found_start;
	int found_level;
	struct extent_buffer *eb;
	struct btrfs_root *root = BTRFS_I(page->mapping->host)->root;
	struct btrfs_fs_info *fs_info = root->fs_info;
	u16 csum_size = btrfs_super_csum_size(fs_info->super_copy);
	int ret = 0;
	u8 result[BTRFS_CSUM_SIZE];
	int reads_done;

	if (!page->private)
		goto out;

	eb = (struct extent_buffer *)page->private;

	/* the pending IO might have been the only thing that kept this buffer
	 * in memory.  Make sure we have a ref for all this other checks
	 */
	extent_buffer_get(eb);

	reads_done = atomic_dec_and_test(&eb->io_pages);
	if (!reads_done)
		goto err;

	eb->read_mirror = mirror;
	if (test_bit(EXTENT_BUFFER_READ_ERR, &eb->bflags)) {
		ret = -EIO;
		goto err;
	}

	found_start = btrfs_header_bytenr(eb);
	if (found_start != eb->start) {
		btrfs_err_rl(fs_info, "bad tree block start, want %llu have %llu",
			     eb->start, found_start);
		ret = -EIO;
		goto err;
	}
	if (check_tree_block_fsid(eb)) {
		btrfs_err_rl(fs_info, "bad fsid on block %llu",
			     eb->start);
		ret = -EIO;
		goto err;
	}
	found_level = btrfs_header_level(eb);
	if (found_level >= BTRFS_MAX_LEVEL) {
		btrfs_err(fs_info, "bad tree block level %d on %llu",
			  (int)btrfs_header_level(eb), eb->start);
		ret = -EIO;
		goto err;
	}

	btrfs_set_buffer_lockdep_class(btrfs_header_owner(eb),
				       eb, found_level);

	ret = csum_tree_block(eb, result);
	if (ret)
		goto err;

	if (memcmp_extent_buffer(eb, result, 0, csum_size)) {
		u32 val;
		u32 found = 0;

		memcpy(&found, result, csum_size);

		read_extent_buffer(eb, &val, 0, csum_size);
		btrfs_warn_rl(fs_info,
		"%s checksum verify failed on %llu wanted %x found %x level %d",
			      fs_info->sb->s_id, eb->start,
			      val, found, btrfs_header_level(eb));
		ret = -EUCLEAN;
		goto err;
	}

	/*
	 * If this is a leaf block and it is corrupt, set the corrupt bit so
	 * that we don't try and read the other copies of this block, just
	 * return -EIO.
	 */
	if (found_level == 0 && btrfs_check_leaf_full(eb)) {
		set_bit(EXTENT_BUFFER_CORRUPT, &eb->bflags);
		ret = -EIO;
	}

	if (found_level > 0 && btrfs_check_node(eb))
		ret = -EIO;

	if (!ret)
		set_extent_buffer_uptodate(eb);
	else
		btrfs_err(fs_info,
			  "block=%llu read time tree block corruption detected",
			  eb->start);
err:
	if (reads_done &&
	    test_and_clear_bit(EXTENT_BUFFER_READAHEAD, &eb->bflags))
		btree_readahead_hook(eb, ret);

	if (ret) {
		/*
		 * our io error hook is going to dec the io pages
		 * again, we have to make sure it has something
		 * to decrement
		 */
		atomic_inc(&eb->io_pages);
		clear_extent_buffer_uptodate(eb);
	}
	free_extent_buffer(eb);
out:
	return ret;
}