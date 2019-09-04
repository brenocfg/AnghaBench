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
typedef  int u64 ;
typedef  unsigned long u16 ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int leave_spinning; int* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ objectid; int offset; scalar_t__ type; } ;
struct btrfs_fs_info {TYPE_1__* sb; int /*<<< orphan*/  super_copy; struct btrfs_root* csum_root; } ;
struct TYPE_2__ {int s_blocksize_bits; } ;

/* Variables and functions */
 scalar_t__ BTRFS_EXTENT_CSUM_KEY ; 
 scalar_t__ BTRFS_EXTENT_CSUM_OBJECTID ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,int) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int btrfs_del_items (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,int,int) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 unsigned long btrfs_item_ptr_offset (struct extent_buffer*,int) ; 
 unsigned long btrfs_item_size_nr (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_slot (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int,int) ; 
 int btrfs_split_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,struct btrfs_key*,unsigned long) ; 
 unsigned long btrfs_super_csum_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memzero_extent_buffer (struct extent_buffer*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  truncate_one_csum (struct btrfs_fs_info*,struct btrfs_path*,struct btrfs_key*,int,int) ; 

int btrfs_del_csums(struct btrfs_trans_handle *trans,
		    struct btrfs_fs_info *fs_info, u64 bytenr, u64 len)
{
	struct btrfs_root *root = fs_info->csum_root;
	struct btrfs_path *path;
	struct btrfs_key key;
	u64 end_byte = bytenr + len;
	u64 csum_end;
	struct extent_buffer *leaf;
	int ret;
	u16 csum_size = btrfs_super_csum_size(fs_info->super_copy);
	int blocksize_bits = fs_info->sb->s_blocksize_bits;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	while (1) {
		key.objectid = BTRFS_EXTENT_CSUM_OBJECTID;
		key.offset = end_byte - 1;
		key.type = BTRFS_EXTENT_CSUM_KEY;

		path->leave_spinning = 1;
		ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
		if (ret > 0) {
			if (path->slots[0] == 0)
				break;
			path->slots[0]--;
		} else if (ret < 0) {
			break;
		}

		leaf = path->nodes[0];
		btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);

		if (key.objectid != BTRFS_EXTENT_CSUM_OBJECTID ||
		    key.type != BTRFS_EXTENT_CSUM_KEY) {
			break;
		}

		if (key.offset >= end_byte)
			break;

		csum_end = btrfs_item_size_nr(leaf, path->slots[0]) / csum_size;
		csum_end <<= blocksize_bits;
		csum_end += key.offset;

		/* this csum ends before we start, we're done */
		if (csum_end <= bytenr)
			break;

		/* delete the entire item, it is inside our range */
		if (key.offset >= bytenr && csum_end <= end_byte) {
			int del_nr = 1;

			/*
			 * Check how many csum items preceding this one in this
			 * leaf correspond to our range and then delete them all
			 * at once.
			 */
			if (key.offset > bytenr && path->slots[0] > 0) {
				int slot = path->slots[0] - 1;

				while (slot >= 0) {
					struct btrfs_key pk;

					btrfs_item_key_to_cpu(leaf, &pk, slot);
					if (pk.offset < bytenr ||
					    pk.type != BTRFS_EXTENT_CSUM_KEY ||
					    pk.objectid !=
					    BTRFS_EXTENT_CSUM_OBJECTID)
						break;
					path->slots[0] = slot;
					del_nr++;
					key.offset = pk.offset;
					slot--;
				}
			}
			ret = btrfs_del_items(trans, root, path,
					      path->slots[0], del_nr);
			if (ret)
				goto out;
			if (key.offset == bytenr)
				break;
		} else if (key.offset < bytenr && csum_end > end_byte) {
			unsigned long offset;
			unsigned long shift_len;
			unsigned long item_offset;
			/*
			 *        [ bytenr - len ]
			 *     [csum                ]
			 *
			 * Our bytes are in the middle of the csum,
			 * we need to split this item and insert a new one.
			 *
			 * But we can't drop the path because the
			 * csum could change, get removed, extended etc.
			 *
			 * The trick here is the max size of a csum item leaves
			 * enough room in the tree block for a single
			 * item header.  So, we split the item in place,
			 * adding a new header pointing to the existing
			 * bytes.  Then we loop around again and we have
			 * a nicely formed csum item that we can neatly
			 * truncate.
			 */
			offset = (bytenr - key.offset) >> blocksize_bits;
			offset *= csum_size;

			shift_len = (len >> blocksize_bits) * csum_size;

			item_offset = btrfs_item_ptr_offset(leaf,
							    path->slots[0]);

			memzero_extent_buffer(leaf, item_offset + offset,
					     shift_len);
			key.offset = bytenr;

			/*
			 * btrfs_split_item returns -EAGAIN when the
			 * item changed size or key
			 */
			ret = btrfs_split_item(trans, root, path, &key, offset);
			if (ret && ret != -EAGAIN) {
				btrfs_abort_transaction(trans, ret);
				goto out;
			}

			key.offset = end_byte - 1;
		} else {
			truncate_one_csum(fs_info, path, &key, bytenr, len);
			if (key.offset < bytenr)
				break;
		}
		btrfs_release_path(path);
	}
	ret = 0;
out:
	btrfs_free_path(path);
	return ret;
}