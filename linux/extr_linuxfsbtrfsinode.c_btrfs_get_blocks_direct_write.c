#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct inode {scalar_t__ i_blkbits; int /*<<< orphan*/  i_sb; } ;
struct extent_map {scalar_t__ block_start; scalar_t__ start; int /*<<< orphan*/  flags; int /*<<< orphan*/  bdev; scalar_t__ len; } ;
struct buffer_head {scalar_t__ b_size; int /*<<< orphan*/  b_bdev; scalar_t__ b_blocknr; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_dio_data {scalar_t__ reserve; scalar_t__ unsubmitted_oe_range_end; int /*<<< orphan*/  overwrite; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {struct btrfs_dio_data* journal_info; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (struct inode*) ; 
 int BTRFS_INODE_NODATACOW ; 
 int BTRFS_ORDERED_NOCOW ; 
 int BTRFS_ORDERED_PREALLOC ; 
 int /*<<< orphan*/  EXTENT_FLAG_PREALLOC ; 
 scalar_t__ EXTENT_MAP_HOLE ; 
 scalar_t__ IS_ERR (struct extent_map*) ; 
 int PTR_ERR (struct extent_map*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct extent_map* btrfs_create_dio_extent (struct inode*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  btrfs_dec_nocow_writers (struct btrfs_fs_info*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_free_reserved_data_space_noquota (struct inode*,scalar_t__,scalar_t__) ; 
 scalar_t__ btrfs_inc_nocow_writers (struct btrfs_fs_info*,scalar_t__) ; 
 struct extent_map* btrfs_new_extent_direct (struct inode*,scalar_t__,scalar_t__) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int can_nocow_extent (struct inode*,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_get_blocks_direct_write(struct extent_map **map,
					 struct buffer_head *bh_result,
					 struct inode *inode,
					 struct btrfs_dio_data *dio_data,
					 u64 start, u64 len)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	struct extent_map *em = *map;
	int ret = 0;

	/*
	 * We don't allocate a new extent in the following cases
	 *
	 * 1) The inode is marked as NODATACOW. In this case we'll just use the
	 * existing extent.
	 * 2) The extent is marked as PREALLOC. We're good to go here and can
	 * just use the extent.
	 *
	 */
	if (test_bit(EXTENT_FLAG_PREALLOC, &em->flags) ||
	    ((BTRFS_I(inode)->flags & BTRFS_INODE_NODATACOW) &&
	     em->block_start != EXTENT_MAP_HOLE)) {
		int type;
		u64 block_start, orig_start, orig_block_len, ram_bytes;

		if (test_bit(EXTENT_FLAG_PREALLOC, &em->flags))
			type = BTRFS_ORDERED_PREALLOC;
		else
			type = BTRFS_ORDERED_NOCOW;
		len = min(len, em->len - (start - em->start));
		block_start = em->block_start + (start - em->start);

		if (can_nocow_extent(inode, start, &len, &orig_start,
				     &orig_block_len, &ram_bytes) == 1 &&
		    btrfs_inc_nocow_writers(fs_info, block_start)) {
			struct extent_map *em2;

			em2 = btrfs_create_dio_extent(inode, start, len,
						      orig_start, block_start,
						      len, orig_block_len,
						      ram_bytes, type);
			btrfs_dec_nocow_writers(fs_info, block_start);
			if (type == BTRFS_ORDERED_PREALLOC) {
				free_extent_map(em);
				*map = em = em2;
			}

			if (em2 && IS_ERR(em2)) {
				ret = PTR_ERR(em2);
				goto out;
			}
			/*
			 * For inode marked NODATACOW or extent marked PREALLOC,
			 * use the existing or preallocated extent, so does not
			 * need to adjust btrfs_space_info's bytes_may_use.
			 */
			btrfs_free_reserved_data_space_noquota(inode, start,
							       len);
			goto skip_cow;
		}
	}

	/* this will cow the extent */
	len = bh_result->b_size;
	free_extent_map(em);
	*map = em = btrfs_new_extent_direct(inode, start, len);
	if (IS_ERR(em)) {
		ret = PTR_ERR(em);
		goto out;
	}

	len = min(len, em->len - (start - em->start));

skip_cow:
	bh_result->b_blocknr = (em->block_start + (start - em->start)) >>
		inode->i_blkbits;
	bh_result->b_size = len;
	bh_result->b_bdev = em->bdev;
	set_buffer_mapped(bh_result);

	if (!test_bit(EXTENT_FLAG_PREALLOC, &em->flags))
		set_buffer_new(bh_result);

	/*
	 * Need to update the i_size under the extent lock so buffered
	 * readers will get the updated i_size when we unlock.
	 */
	if (!dio_data->overwrite && start + len > i_size_read(inode))
		i_size_write(inode, start + len);

	WARN_ON(dio_data->reserve < len);
	dio_data->reserve -= len;
	dio_data->unsubmitted_oe_range_end = start + len;
	current->journal_info = dio_data;
out:
	return ret;
}