#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* u64 ;
typedef  scalar_t__ u32 ;
struct root_entry {int /*<<< orphan*/  num_refs; } ;
struct ref_entry {scalar_t__ num_refs; void* offset; void* root_objectid; void* owner; scalar_t__ parent; } ;
struct extent_buffer {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  ref_verify_lock; } ;
struct btrfs_extent_data_ref {int dummy; } ;
struct block_entry {int /*<<< orphan*/  roots; int /*<<< orphan*/  refs; int /*<<< orphan*/  num_refs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct block_entry*) ; 
 int PTR_ERR (struct block_entry*) ; 
 struct block_entry* add_block_entry (struct btrfs_fs_info*,void*,void*,void*) ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*) ; 
 scalar_t__ btrfs_extent_data_ref_count (struct extent_buffer*,struct btrfs_extent_data_ref*) ; 
 void* btrfs_extent_data_ref_objectid (struct extent_buffer*,struct btrfs_extent_data_ref*) ; 
 void* btrfs_extent_data_ref_offset (struct extent_buffer*,struct btrfs_extent_data_ref*) ; 
 void* btrfs_extent_data_ref_root (struct extent_buffer*,struct btrfs_extent_data_ref*) ; 
 scalar_t__ insert_ref_entry (int /*<<< orphan*/ *,struct ref_entry*) ; 
 int /*<<< orphan*/  kfree (struct ref_entry*) ; 
 struct ref_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct root_entry* lookup_root_entry (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_extent_data_ref(struct btrfs_fs_info *fs_info,
			       struct extent_buffer *leaf,
			       struct btrfs_extent_data_ref *dref,
			       u64 bytenr, u64 num_bytes)
{
	struct block_entry *be;
	struct ref_entry *ref;
	struct root_entry *re;
	u64 ref_root = btrfs_extent_data_ref_root(leaf, dref);
	u64 owner = btrfs_extent_data_ref_objectid(leaf, dref);
	u64 offset = btrfs_extent_data_ref_offset(leaf, dref);
	u32 num_refs = btrfs_extent_data_ref_count(leaf, dref);

	ref = kzalloc(sizeof(struct ref_entry), GFP_KERNEL);
	if (!ref)
		return -ENOMEM;
	be = add_block_entry(fs_info, bytenr, num_bytes, ref_root);
	if (IS_ERR(be)) {
		kfree(ref);
		return PTR_ERR(be);
	}
	be->num_refs += num_refs;

	ref->parent = 0;
	ref->owner = owner;
	ref->root_objectid = ref_root;
	ref->offset = offset;
	ref->num_refs = num_refs;
	if (insert_ref_entry(&be->refs, ref)) {
		spin_unlock(&fs_info->ref_verify_lock);
		btrfs_err(fs_info, "existing ref when reading from disk?");
		kfree(ref);
		return -EINVAL;
	}

	re = lookup_root_entry(&be->roots, ref_root);
	if (!re) {
		spin_unlock(&fs_info->ref_verify_lock);
		btrfs_err(fs_info, "missing root in new block entry?");
		return -EINVAL;
	}
	re->num_refs += num_refs;
	spin_unlock(&fs_info->ref_verify_lock);
	return 0;
}