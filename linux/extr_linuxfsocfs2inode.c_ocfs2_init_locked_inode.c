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
struct ocfs2_find_inode_args {size_t fi_sysfile_type; int /*<<< orphan*/  fi_blkno; int /*<<< orphan*/  fi_ino; } ;
struct lock_class_key {int dummy; } ;
struct inode {int /*<<< orphan*/  i_rwsem; int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_alloc_sem; int /*<<< orphan*/  ip_blkno; } ;

/* Variables and functions */
 size_t GROUP_QUOTA_SYSTEM_INODE ; 
 size_t LOCAL_GROUP_QUOTA_SYSTEM_INODE ; 
 size_t LOCAL_USER_QUOTA_SYSTEM_INODE ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 size_t USER_QUOTA_SYSTEM_INODE ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,struct lock_class_key*) ; 
 struct lock_class_key* ocfs2_sysfile_lock_key ; 

__attribute__((used)) static int ocfs2_init_locked_inode(struct inode *inode, void *opaque)
{
	struct ocfs2_find_inode_args *args = opaque;
	static struct lock_class_key ocfs2_quota_ip_alloc_sem_key,
				     ocfs2_file_ip_alloc_sem_key;

	inode->i_ino = args->fi_ino;
	OCFS2_I(inode)->ip_blkno = args->fi_blkno;
	if (args->fi_sysfile_type != 0)
		lockdep_set_class(&inode->i_rwsem,
			&ocfs2_sysfile_lock_key[args->fi_sysfile_type]);
	if (args->fi_sysfile_type == USER_QUOTA_SYSTEM_INODE ||
	    args->fi_sysfile_type == GROUP_QUOTA_SYSTEM_INODE ||
	    args->fi_sysfile_type == LOCAL_USER_QUOTA_SYSTEM_INODE ||
	    args->fi_sysfile_type == LOCAL_GROUP_QUOTA_SYSTEM_INODE)
		lockdep_set_class(&OCFS2_I(inode)->ip_alloc_sem,
				  &ocfs2_quota_ip_alloc_sem_key);
	else
		lockdep_set_class(&OCFS2_I(inode)->ip_alloc_sem,
				  &ocfs2_file_ip_alloc_sem_key);

	return 0;
}