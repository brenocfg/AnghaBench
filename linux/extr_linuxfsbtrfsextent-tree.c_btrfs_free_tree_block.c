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
typedef  int /*<<< orphan*/  u64 ;
struct extent_buffer {int /*<<< orphan*/  bflags; int /*<<< orphan*/  len; int /*<<< orphan*/  start; } ;
struct btrfs_trans_handle {scalar_t__ transid; } ;
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {TYPE_1__ root_key; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_block_group_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DROP_DELAYED_REF ; 
 int /*<<< orphan*/  BTRFS_HEADER_FLAG_WRITTEN ; 
 int /*<<< orphan*/  BTRFS_TREE_LOG_OBJECTID ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EXTENT_BUFFER_CORRUPT ; 
 int /*<<< orphan*/  EXTENT_BUFFER_DIRTY ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_pinned_bytes (struct btrfs_fs_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int btrfs_add_delayed_tree_ref (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  btrfs_add_free_space (struct btrfs_block_group_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_free_reserved_bytes (struct btrfs_block_group_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_header_flag (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_header_generation (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_header_level (struct extent_buffer*) ; 
 struct btrfs_block_group_cache* btrfs_lookup_block_group (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  btrfs_ref_tree_mod (struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int check_ref_cleanup (struct btrfs_trans_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pin_down_extent (struct btrfs_fs_info*,struct btrfs_block_group_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_reserved_extent_free (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btrfs_free_tree_block(struct btrfs_trans_handle *trans,
			   struct btrfs_root *root,
			   struct extent_buffer *buf,
			   u64 parent, int last_ref)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	int pin = 1;
	int ret;

	if (root->root_key.objectid != BTRFS_TREE_LOG_OBJECTID) {
		int old_ref_mod, new_ref_mod;

		btrfs_ref_tree_mod(root, buf->start, buf->len, parent,
				   root->root_key.objectid,
				   btrfs_header_level(buf), 0,
				   BTRFS_DROP_DELAYED_REF);
		ret = btrfs_add_delayed_tree_ref(trans, buf->start,
						 buf->len, parent,
						 root->root_key.objectid,
						 btrfs_header_level(buf),
						 BTRFS_DROP_DELAYED_REF, NULL,
						 &old_ref_mod, &new_ref_mod);
		BUG_ON(ret); /* -ENOMEM */
		pin = old_ref_mod >= 0 && new_ref_mod < 0;
	}

	if (last_ref && btrfs_header_generation(buf) == trans->transid) {
		struct btrfs_block_group_cache *cache;

		if (root->root_key.objectid != BTRFS_TREE_LOG_OBJECTID) {
			ret = check_ref_cleanup(trans, buf->start);
			if (!ret)
				goto out;
		}

		pin = 0;
		cache = btrfs_lookup_block_group(fs_info, buf->start);

		if (btrfs_header_flag(buf, BTRFS_HEADER_FLAG_WRITTEN)) {
			pin_down_extent(fs_info, cache, buf->start,
					buf->len, 1);
			btrfs_put_block_group(cache);
			goto out;
		}

		WARN_ON(test_bit(EXTENT_BUFFER_DIRTY, &buf->bflags));

		btrfs_add_free_space(cache, buf->start, buf->len);
		btrfs_free_reserved_bytes(cache, buf->len, 0);
		btrfs_put_block_group(cache);
		trace_btrfs_reserved_extent_free(fs_info, buf->start, buf->len);
	}
out:
	if (pin)
		add_pinned_bytes(fs_info, buf->len, true,
				 root->root_key.objectid);

	if (last_ref) {
		/*
		 * Deleting the buffer, clear the corrupt flag since it doesn't
		 * matter anymore.
		 */
		clear_bit(EXTENT_BUFFER_CORRUPT, &buf->bflags);
	}
}