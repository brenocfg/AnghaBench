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
struct root_entry {void* roots; int /*<<< orphan*/  actions; void* refs; scalar_t__ from_disk; scalar_t__ metadata; scalar_t__ num_refs; void* root_objectid; void* len; void* bytenr; } ;
struct btrfs_fs_info {int /*<<< orphan*/  block_tree; int /*<<< orphan*/  ref_verify_lock; } ;
struct block_entry {void* roots; int /*<<< orphan*/  actions; void* refs; scalar_t__ from_disk; scalar_t__ metadata; scalar_t__ num_refs; void* root_objectid; void* len; void* bytenr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct root_entry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* RB_ROOT ; 
 struct root_entry* insert_block_entry (int /*<<< orphan*/ *,struct root_entry*) ; 
 struct root_entry* insert_root_entry (void**,struct root_entry*) ; 
 int /*<<< orphan*/  kfree (struct root_entry*) ; 
 struct root_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct block_entry *add_block_entry(struct btrfs_fs_info *fs_info,
					   u64 bytenr, u64 len,
					   u64 root_objectid)
{
	struct block_entry *be = NULL, *exist;
	struct root_entry *re = NULL;

	re = kzalloc(sizeof(struct root_entry), GFP_KERNEL);
	be = kzalloc(sizeof(struct block_entry), GFP_KERNEL);
	if (!be || !re) {
		kfree(re);
		kfree(be);
		return ERR_PTR(-ENOMEM);
	}
	be->bytenr = bytenr;
	be->len = len;

	re->root_objectid = root_objectid;
	re->num_refs = 0;

	spin_lock(&fs_info->ref_verify_lock);
	exist = insert_block_entry(&fs_info->block_tree, be);
	if (exist) {
		if (root_objectid) {
			struct root_entry *exist_re;

			exist_re = insert_root_entry(&exist->roots, re);
			if (exist_re)
				kfree(re);
		}
		kfree(be);
		return exist;
	}

	be->num_refs = 0;
	be->metadata = 0;
	be->from_disk = 0;
	be->roots = RB_ROOT;
	be->refs = RB_ROOT;
	INIT_LIST_HEAD(&be->actions);
	if (root_objectid)
		insert_root_entry(&be->roots, re);
	else
		kfree(re);
	return be;
}