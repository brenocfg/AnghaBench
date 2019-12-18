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
struct TYPE_2__ {int /*<<< orphan*/  fs_kobj_unregister; int /*<<< orphan*/  fs_kobj; int /*<<< orphan*/  fs_fcheck; } ;
struct ocfs2_super {TYPE_1__ osb_fc_ent; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_filecheck_sysfs_free (TYPE_1__*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void ocfs2_filecheck_remove_sysfs(struct ocfs2_super *osb)
{
	if (!osb->osb_fc_ent.fs_fcheck)
		return;

	kobject_del(&osb->osb_fc_ent.fs_kobj);
	kobject_put(&osb->osb_fc_ent.fs_kobj);
	wait_for_completion(&osb->osb_fc_ent.fs_kobj_unregister);
	ocfs2_filecheck_sysfs_free(&osb->osb_fc_ent);
}