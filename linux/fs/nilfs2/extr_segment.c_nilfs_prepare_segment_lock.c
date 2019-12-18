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
struct super_block {int dummy; } ;
struct nilfs_transaction_info {scalar_t__ ti_magic; int ti_count; void* ti_save; scalar_t__ ti_flags; } ;
struct TYPE_2__ {struct nilfs_transaction_info* journal_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 scalar_t__ NILFS_TI_DYNAMIC_ALLOC ; 
 scalar_t__ NILFS_TI_MAGIC ; 
 TYPE_1__* current ; 
 struct nilfs_transaction_info* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nilfs_transaction_cachep ; 

__attribute__((used)) static int nilfs_prepare_segment_lock(struct super_block *sb,
				      struct nilfs_transaction_info *ti)
{
	struct nilfs_transaction_info *cur_ti = current->journal_info;
	void *save = NULL;

	if (cur_ti) {
		if (cur_ti->ti_magic == NILFS_TI_MAGIC)
			return ++cur_ti->ti_count;

		/*
		 * If journal_info field is occupied by other FS,
		 * it is saved and will be restored on
		 * nilfs_transaction_commit().
		 */
		nilfs_msg(sb, KERN_WARNING, "journal info from a different FS");
		save = current->journal_info;
	}
	if (!ti) {
		ti = kmem_cache_alloc(nilfs_transaction_cachep, GFP_NOFS);
		if (!ti)
			return -ENOMEM;
		ti->ti_flags = NILFS_TI_DYNAMIC_ALLOC;
	} else {
		ti->ti_flags = 0;
	}
	ti->ti_count = 0;
	ti->ti_save = save;
	ti->ti_magic = NILFS_TI_MAGIC;
	current->journal_info = ti;
	return 0;
}