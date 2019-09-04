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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u64 ;
struct btrfs_trans_handle {TYPE_1__* transaction; struct btrfs_fs_info* fs_info; } ;
struct btrfs_qgroup_extent_record {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  flags; } ;
struct btrfs_delayed_tree_ref {int level; int /*<<< orphan*/  node; struct btrfs_delayed_extent_op* extent_op; void* parent; void* root; } ;
struct btrfs_delayed_ref_root {int /*<<< orphan*/  lock; } ;
struct btrfs_delayed_ref_head {int level; int /*<<< orphan*/  node; struct btrfs_delayed_extent_op* extent_op; void* parent; void* root; } ;
struct btrfs_delayed_extent_op {scalar_t__ is_data; } ;
struct TYPE_2__ {struct btrfs_delayed_ref_root delayed_refs; } ;

/* Variables and functions */
 int BTRFS_ADD_DELAYED_EXTENT ; 
 int BTRFS_ADD_DELAYED_REF ; 
 void* BTRFS_CHUNK_TREE_OBJECTID ; 
 int /*<<< orphan*/  BTRFS_FS_QUOTA_ENABLED ; 
 int /*<<< orphan*/  BTRFS_SHARED_BLOCK_REF_KEY ; 
 int /*<<< orphan*/  BTRFS_TREE_BLOCK_REF_KEY ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct btrfs_delayed_tree_ref* add_delayed_ref_head (struct btrfs_trans_handle*,struct btrfs_delayed_tree_ref*,struct btrfs_qgroup_extent_record*,int,int*,int*,int*) ; 
 int /*<<< orphan*/  btrfs_delayed_ref_head_cachep ; 
 int /*<<< orphan*/  btrfs_delayed_tree_ref_cachep ; 
 int /*<<< orphan*/  btrfs_qgroup_trace_extent_post (struct btrfs_fs_info*,struct btrfs_qgroup_extent_record*) ; 
 int /*<<< orphan*/  init_delayed_ref_common (struct btrfs_fs_info*,int /*<<< orphan*/ *,void*,void*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_delayed_ref_head (struct btrfs_delayed_tree_ref*,struct btrfs_qgroup_extent_record*,void*,void*,void*,int /*<<< orphan*/ ,int,int,int) ; 
 int insert_delayed_ref (struct btrfs_trans_handle*,struct btrfs_delayed_ref_root*,struct btrfs_delayed_tree_ref*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_fstree (void*) ; 
 struct btrfs_qgroup_extent_record* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct btrfs_delayed_tree_ref* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct btrfs_delayed_tree_ref*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_add_delayed_tree_ref (struct btrfs_fs_info*,int /*<<< orphan*/ *,struct btrfs_delayed_tree_ref*,int) ; 

int btrfs_add_delayed_tree_ref(struct btrfs_trans_handle *trans,
			       u64 bytenr, u64 num_bytes, u64 parent,
			       u64 ref_root,  int level, int action,
			       struct btrfs_delayed_extent_op *extent_op,
			       int *old_ref_mod, int *new_ref_mod)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_delayed_tree_ref *ref;
	struct btrfs_delayed_ref_head *head_ref;
	struct btrfs_delayed_ref_root *delayed_refs;
	struct btrfs_qgroup_extent_record *record = NULL;
	int qrecord_inserted;
	bool is_system = (ref_root == BTRFS_CHUNK_TREE_OBJECTID);
	int ret;
	u8 ref_type;

	BUG_ON(extent_op && extent_op->is_data);
	ref = kmem_cache_alloc(btrfs_delayed_tree_ref_cachep, GFP_NOFS);
	if (!ref)
		return -ENOMEM;

	head_ref = kmem_cache_alloc(btrfs_delayed_ref_head_cachep, GFP_NOFS);
	if (!head_ref) {
		kmem_cache_free(btrfs_delayed_tree_ref_cachep, ref);
		return -ENOMEM;
	}

	if (test_bit(BTRFS_FS_QUOTA_ENABLED, &fs_info->flags) &&
	    is_fstree(ref_root)) {
		record = kmalloc(sizeof(*record), GFP_NOFS);
		if (!record) {
			kmem_cache_free(btrfs_delayed_tree_ref_cachep, ref);
			kmem_cache_free(btrfs_delayed_ref_head_cachep, head_ref);
			return -ENOMEM;
		}
	}

	if (parent)
		ref_type = BTRFS_SHARED_BLOCK_REF_KEY;
	else
		ref_type = BTRFS_TREE_BLOCK_REF_KEY;

	init_delayed_ref_common(fs_info, &ref->node, bytenr, num_bytes,
				ref_root, action, ref_type);
	ref->root = ref_root;
	ref->parent = parent;
	ref->level = level;

	init_delayed_ref_head(head_ref, record, bytenr, num_bytes,
			      ref_root, 0, action, false, is_system);
	head_ref->extent_op = extent_op;

	delayed_refs = &trans->transaction->delayed_refs;
	spin_lock(&delayed_refs->lock);

	/*
	 * insert both the head node and the new ref without dropping
	 * the spin lock
	 */
	head_ref = add_delayed_ref_head(trans, head_ref, record,
					action, &qrecord_inserted,
					old_ref_mod, new_ref_mod);

	ret = insert_delayed_ref(trans, delayed_refs, head_ref, &ref->node);
	spin_unlock(&delayed_refs->lock);

	trace_add_delayed_tree_ref(fs_info, &ref->node, ref,
				   action == BTRFS_ADD_DELAYED_EXTENT ?
				   BTRFS_ADD_DELAYED_REF : action);
	if (ret > 0)
		kmem_cache_free(btrfs_delayed_tree_ref_cachep, ref);

	if (qrecord_inserted)
		btrfs_qgroup_trace_extent_post(fs_info, record);

	return 0;
}