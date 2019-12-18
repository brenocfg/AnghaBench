#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kset; } ;
struct ocfs2_filecheck_sysfs_entry {struct ocfs2_filecheck* fs_fcheck; TYPE_1__ fs_kobj; int /*<<< orphan*/  fs_kobj_unregister; } ;
struct ocfs2_super {int /*<<< orphan*/  osb_dev_kset; struct ocfs2_filecheck_sysfs_entry osb_fc_ent; } ;
struct ocfs2_filecheck {scalar_t__ fc_done; scalar_t__ fc_size; int /*<<< orphan*/  fc_max; int /*<<< orphan*/  fc_lock; int /*<<< orphan*/  fc_head; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCFS2_FILECHECK_MINSIZE ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_filecheck*) ; 
 struct ocfs2_filecheck* kmalloc (int,int /*<<< orphan*/ ) ; 
 int kobject_init_and_add (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kobject_put (TYPE_1__*) ; 
 int /*<<< orphan*/  ocfs2_ktype_filecheck ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int ocfs2_filecheck_create_sysfs(struct ocfs2_super *osb)
{
	int ret;
	struct ocfs2_filecheck *fcheck;
	struct ocfs2_filecheck_sysfs_entry *entry = &osb->osb_fc_ent;

	fcheck = kmalloc(sizeof(struct ocfs2_filecheck), GFP_NOFS);
	if (!fcheck)
		return -ENOMEM;

	INIT_LIST_HEAD(&fcheck->fc_head);
	spin_lock_init(&fcheck->fc_lock);
	fcheck->fc_max = OCFS2_FILECHECK_MINSIZE;
	fcheck->fc_size = 0;
	fcheck->fc_done = 0;

	entry->fs_kobj.kset = osb->osb_dev_kset;
	init_completion(&entry->fs_kobj_unregister);
	ret = kobject_init_and_add(&entry->fs_kobj, &ocfs2_ktype_filecheck,
					NULL, "filecheck");
	if (ret) {
		kobject_put(&entry->fs_kobj);
		kfree(fcheck);
		return ret;
	}

	entry->fs_fcheck = fcheck;
	return 0;
}