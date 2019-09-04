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
typedef  struct root_entry* u64 ;
struct root_entry {int /*<<< orphan*/  num_refs; } ;
struct ref_entry {int owner; int num_refs; scalar_t__ offset; struct root_entry* parent; struct root_entry* root_objectid; } ;
struct btrfs_fs_info {int /*<<< orphan*/  ref_verify_lock; int /*<<< orphan*/  nodesize; } ;
struct block_entry {int from_disk; int metadata; int /*<<< orphan*/  refs; int /*<<< orphan*/  roots; int /*<<< orphan*/  num_refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct root_entry*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct block_entry*) ; 
 int PTR_ERR (struct block_entry*) ; 
 struct block_entry* add_block_entry (struct btrfs_fs_info*,struct root_entry*,int /*<<< orphan*/ ,struct root_entry*) ; 
 struct ref_entry* insert_ref_entry (int /*<<< orphan*/ *,struct ref_entry*) ; 
 int /*<<< orphan*/  kfree (struct ref_entry*) ; 
 struct ref_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct root_entry* lookup_root_entry (int /*<<< orphan*/ *,struct root_entry*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_tree_block(struct btrfs_fs_info *fs_info, u64 ref_root,
			  u64 parent, u64 bytenr, int level)
{
	struct block_entry *be;
	struct root_entry *re;
	struct ref_entry *ref = NULL, *exist;

	ref = kmalloc(sizeof(struct ref_entry), GFP_KERNEL);
	if (!ref)
		return -ENOMEM;

	if (parent)
		ref->root_objectid = 0;
	else
		ref->root_objectid = ref_root;
	ref->parent = parent;
	ref->owner = level;
	ref->offset = 0;
	ref->num_refs = 1;

	be = add_block_entry(fs_info, bytenr, fs_info->nodesize, ref_root);
	if (IS_ERR(be)) {
		kfree(ref);
		return PTR_ERR(be);
	}
	be->num_refs++;
	be->from_disk = 1;
	be->metadata = 1;

	if (!parent) {
		ASSERT(ref_root);
		re = lookup_root_entry(&be->roots, ref_root);
		ASSERT(re);
		re->num_refs++;
	}
	exist = insert_ref_entry(&be->refs, ref);
	if (exist) {
		exist->num_refs++;
		kfree(ref);
	}
	spin_unlock(&fs_info->ref_verify_lock);

	return 0;
}