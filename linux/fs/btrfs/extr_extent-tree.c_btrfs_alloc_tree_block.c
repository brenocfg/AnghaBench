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
typedef  scalar_t__ u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  objectid; } ;
struct btrfs_root {TYPE_1__ root_key; int /*<<< orphan*/  alloc_bytenr; struct btrfs_fs_info* fs_info; } ;
struct btrfs_ref {int /*<<< orphan*/  real_root; int /*<<< orphan*/  member_0; } ;
struct btrfs_key {int /*<<< orphan*/  offset; int /*<<< orphan*/  objectid; } ;
struct btrfs_fs_info {scalar_t__ nodesize; } ;
struct btrfs_disk_key {int dummy; } ;
struct btrfs_delayed_extent_op {int update_key; int update_flags; int is_data; int level; int /*<<< orphan*/  flags_to_set; int /*<<< orphan*/  key; } ;
typedef  struct extent_buffer btrfs_block_rsv ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ADD_DELAYED_EXTENT ; 
 int /*<<< orphan*/  BTRFS_BLOCK_FLAG_FULL_BACKREF ; 
 int /*<<< orphan*/  BTRFS_TREE_LOG_OBJECTID ; 
 int /*<<< orphan*/  BTRFS_TREE_RELOC_OBJECTID ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 struct extent_buffer* ERR_CAST (struct extent_buffer*) ; 
 struct extent_buffer* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct extent_buffer*) ; 
 int PTR_ERR (struct extent_buffer*) ; 
 int /*<<< orphan*/  SKINNY_METADATA ; 
 int btrfs_add_delayed_tree_ref (struct btrfs_trans_handle*,struct btrfs_ref*,struct btrfs_delayed_extent_op*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct btrfs_delayed_extent_op* btrfs_alloc_delayed_extent_op () ; 
 int /*<<< orphan*/  btrfs_free_delayed_extent_op (struct btrfs_delayed_extent_op*) ; 
 int /*<<< orphan*/  btrfs_free_reserved_extent (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_fs_incompat (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_init_generic_ref (struct btrfs_ref*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct extent_buffer* btrfs_init_new_buffer (struct btrfs_trans_handle*,struct btrfs_root*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_init_tree_ref (struct btrfs_ref*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_is_testing (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_ref_tree_mod (struct btrfs_fs_info*,struct btrfs_ref*) ; 
 int btrfs_reserve_extent (struct btrfs_root*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct btrfs_key*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_unuse_block_rsv (struct btrfs_fs_info*,struct extent_buffer*,scalar_t__) ; 
 struct extent_buffer* btrfs_use_block_rsv (struct btrfs_trans_handle*,struct btrfs_root*,scalar_t__) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct btrfs_disk_key const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

struct extent_buffer *btrfs_alloc_tree_block(struct btrfs_trans_handle *trans,
					     struct btrfs_root *root,
					     u64 parent, u64 root_objectid,
					     const struct btrfs_disk_key *key,
					     int level, u64 hint,
					     u64 empty_size)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_key ins;
	struct btrfs_block_rsv *block_rsv;
	struct extent_buffer *buf;
	struct btrfs_delayed_extent_op *extent_op;
	struct btrfs_ref generic_ref = { 0 };
	u64 flags = 0;
	int ret;
	u32 blocksize = fs_info->nodesize;
	bool skinny_metadata = btrfs_fs_incompat(fs_info, SKINNY_METADATA);

#ifdef CONFIG_BTRFS_FS_RUN_SANITY_TESTS
	if (btrfs_is_testing(fs_info)) {
		buf = btrfs_init_new_buffer(trans, root, root->alloc_bytenr,
					    level, root_objectid);
		if (!IS_ERR(buf))
			root->alloc_bytenr += blocksize;
		return buf;
	}
#endif

	block_rsv = btrfs_use_block_rsv(trans, root, blocksize);
	if (IS_ERR(block_rsv))
		return ERR_CAST(block_rsv);

	ret = btrfs_reserve_extent(root, blocksize, blocksize, blocksize,
				   empty_size, hint, &ins, 0, 0);
	if (ret)
		goto out_unuse;

	buf = btrfs_init_new_buffer(trans, root, ins.objectid, level,
				    root_objectid);
	if (IS_ERR(buf)) {
		ret = PTR_ERR(buf);
		goto out_free_reserved;
	}

	if (root_objectid == BTRFS_TREE_RELOC_OBJECTID) {
		if (parent == 0)
			parent = ins.objectid;
		flags |= BTRFS_BLOCK_FLAG_FULL_BACKREF;
	} else
		BUG_ON(parent > 0);

	if (root_objectid != BTRFS_TREE_LOG_OBJECTID) {
		extent_op = btrfs_alloc_delayed_extent_op();
		if (!extent_op) {
			ret = -ENOMEM;
			goto out_free_buf;
		}
		if (key)
			memcpy(&extent_op->key, key, sizeof(extent_op->key));
		else
			memset(&extent_op->key, 0, sizeof(extent_op->key));
		extent_op->flags_to_set = flags;
		extent_op->update_key = skinny_metadata ? false : true;
		extent_op->update_flags = true;
		extent_op->is_data = false;
		extent_op->level = level;

		btrfs_init_generic_ref(&generic_ref, BTRFS_ADD_DELAYED_EXTENT,
				       ins.objectid, ins.offset, parent);
		generic_ref.real_root = root->root_key.objectid;
		btrfs_init_tree_ref(&generic_ref, level, root_objectid);
		btrfs_ref_tree_mod(fs_info, &generic_ref);
		ret = btrfs_add_delayed_tree_ref(trans, &generic_ref,
						 extent_op, NULL, NULL);
		if (ret)
			goto out_free_delayed;
	}
	return buf;

out_free_delayed:
	btrfs_free_delayed_extent_op(extent_op);
out_free_buf:
	free_extent_buffer(buf);
out_free_reserved:
	btrfs_free_reserved_extent(fs_info, ins.objectid, ins.offset, 0);
out_unuse:
	btrfs_unuse_block_rsv(fs_info, block_rsv, blocksize);
	return ERR_PTR(ret);
}