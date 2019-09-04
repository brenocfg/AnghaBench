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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {int /*<<< orphan*/  sys_root_inode; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  namebuf ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_FI_FLAG_SYSFILE ; 
 int /*<<< orphan*/  PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int /*<<< orphan*/ ) ; 
 struct inode* ocfs2_iget (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ocfs2_lookup_ino_from_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_sprintf_system_inode_name (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static struct inode * _ocfs2_get_system_file_inode(struct ocfs2_super *osb,
						   int type,
						   u32 slot)
{
	char namebuf[40];
	struct inode *inode = NULL;
	u64 blkno;
	int status = 0;

	ocfs2_sprintf_system_inode_name(namebuf,
					sizeof(namebuf),
					type, slot);

	status = ocfs2_lookup_ino_from_name(osb->sys_root_inode, namebuf,
					    strlen(namebuf), &blkno);
	if (status < 0) {
		goto bail;
	}

	inode = ocfs2_iget(osb, blkno, OCFS2_FI_FLAG_SYSFILE, type);
	if (IS_ERR(inode)) {
		mlog_errno(PTR_ERR(inode));
		inode = NULL;
		goto bail;
	}
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	if (type == LOCAL_USER_QUOTA_SYSTEM_INODE ||
	    type == LOCAL_GROUP_QUOTA_SYSTEM_INODE ||
	    type == JOURNAL_SYSTEM_INODE) {
		/* Ignore inode lock on these inodes as the lock does not
		 * really belong to any process and lockdep cannot handle
		 * that */
		OCFS2_I(inode)->ip_inode_lockres.l_lockdep_map.key = NULL;
	} else {
		lockdep_init_map(&OCFS2_I(inode)->ip_inode_lockres.
								l_lockdep_map,
				 ocfs2_system_inodes[type].si_name,
				 &ocfs2_sysfile_cluster_lock_key[type], 0);
	}
#endif
bail:

	return inode;
}