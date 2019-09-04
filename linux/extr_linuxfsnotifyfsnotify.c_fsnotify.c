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
typedef  int /*<<< orphan*/  u32 ;
struct path {int /*<<< orphan*/  mnt; } ;
struct mount {int mnt_fsnotify_mask; int /*<<< orphan*/  mnt_fsnotify_marks; } ;
struct inode {int i_fsnotify_mask; int /*<<< orphan*/  i_fsnotify_marks; } ;
struct fsnotify_iter_info {int /*<<< orphan*/  srcu_idx; void** marks; } ;
typedef  int __u32 ;

/* Variables and functions */
 int ALL_FSNOTIFY_EVENTS ; 
 int ALL_FSNOTIFY_PERM_EVENTS ; 
 int FSNOTIFY_EVENT_PATH ; 
 size_t FSNOTIFY_OBJ_TYPE_INODE ; 
 size_t FSNOTIFY_OBJ_TYPE_VFSMOUNT ; 
 int FS_EVENT_ON_CHILD ; 
 int FS_MODIFY ; 
 void* fsnotify_first_mark (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_iter_next (struct fsnotify_iter_info*) ; 
 scalar_t__ fsnotify_iter_select_report_types (struct fsnotify_iter_info*) ; 
 int /*<<< orphan*/  fsnotify_mark_srcu ; 
 struct mount* real_mount (int /*<<< orphan*/ ) ; 
 int send_to_group (struct inode*,int,void const*,int,int /*<<< orphan*/ ,unsigned char const*,struct fsnotify_iter_info*) ; 
 int /*<<< orphan*/  srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int fsnotify(struct inode *to_tell, __u32 mask, const void *data, int data_is,
	     const unsigned char *file_name, u32 cookie)
{
	struct fsnotify_iter_info iter_info = {};
	struct mount *mnt;
	int ret = 0;
	__u32 test_mask = (mask & ALL_FSNOTIFY_EVENTS);

	if (data_is == FSNOTIFY_EVENT_PATH)
		mnt = real_mount(((const struct path *)data)->mnt);
	else
		mnt = NULL;

	/* An event "on child" is not intended for a mount mark */
	if (mask & FS_EVENT_ON_CHILD)
		mnt = NULL;

	/*
	 * Optimization: srcu_read_lock() has a memory barrier which can
	 * be expensive.  It protects walking the *_fsnotify_marks lists.
	 * However, if we do not walk the lists, we do not have to do
	 * SRCU because we have no references to any objects and do not
	 * need SRCU to keep them "alive".
	 */
	if (!to_tell->i_fsnotify_marks &&
	    (!mnt || !mnt->mnt_fsnotify_marks))
		return 0;
	/*
	 * if this is a modify event we may need to clear the ignored masks
	 * otherwise return if neither the inode nor the vfsmount care about
	 * this type of event.
	 */
	if (!(mask & FS_MODIFY) &&
	    !(test_mask & to_tell->i_fsnotify_mask) &&
	    !(mnt && test_mask & mnt->mnt_fsnotify_mask))
		return 0;

	iter_info.srcu_idx = srcu_read_lock(&fsnotify_mark_srcu);

	iter_info.marks[FSNOTIFY_OBJ_TYPE_INODE] =
		fsnotify_first_mark(&to_tell->i_fsnotify_marks);
	if (mnt) {
		iter_info.marks[FSNOTIFY_OBJ_TYPE_VFSMOUNT] =
			fsnotify_first_mark(&mnt->mnt_fsnotify_marks);
	}

	/*
	 * We need to merge inode & vfsmount mark lists so that inode mark
	 * ignore masks are properly reflected for mount mark notifications.
	 * That's why this traversal is so complicated...
	 */
	while (fsnotify_iter_select_report_types(&iter_info)) {
		ret = send_to_group(to_tell, mask, data, data_is, cookie,
				    file_name, &iter_info);

		if (ret && (mask & ALL_FSNOTIFY_PERM_EVENTS))
			goto out;

		fsnotify_iter_next(&iter_info);
	}
	ret = 0;
out:
	srcu_read_unlock(&fsnotify_mark_srcu, iter_info.srcu_idx);

	return ret;
}