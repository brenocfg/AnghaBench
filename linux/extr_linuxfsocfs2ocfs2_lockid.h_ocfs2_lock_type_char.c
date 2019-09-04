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
typedef  enum ocfs2_lock_type { ____Placeholder_ocfs2_lock_type } ocfs2_lock_type ;

/* Variables and functions */
#define  OCFS2_LOCK_TYPE_DATA 140 
#define  OCFS2_LOCK_TYPE_DENTRY 139 
#define  OCFS2_LOCK_TYPE_FLOCK 138 
#define  OCFS2_LOCK_TYPE_META 137 
#define  OCFS2_LOCK_TYPE_NFS_SYNC 136 
#define  OCFS2_LOCK_TYPE_OPEN 135 
#define  OCFS2_LOCK_TYPE_ORPHAN_SCAN 134 
#define  OCFS2_LOCK_TYPE_QINFO 133 
#define  OCFS2_LOCK_TYPE_REFCOUNT 132 
#define  OCFS2_LOCK_TYPE_RENAME 131 
#define  OCFS2_LOCK_TYPE_RW 130 
#define  OCFS2_LOCK_TYPE_SUPER 129 
#define  OCFS2_LOCK_TYPE_TRIM_FS 128 

__attribute__((used)) static inline char ocfs2_lock_type_char(enum ocfs2_lock_type type)
{
	char c;
	switch (type) {
		case OCFS2_LOCK_TYPE_META:
			c = 'M';
			break;
		case OCFS2_LOCK_TYPE_DATA:
			c = 'D';
			break;
		case OCFS2_LOCK_TYPE_SUPER:
			c = 'S';
			break;
		case OCFS2_LOCK_TYPE_RENAME:
			c = 'R';
			break;
		case OCFS2_LOCK_TYPE_RW:
			c = 'W';
			break;
		case OCFS2_LOCK_TYPE_DENTRY:
			c = 'N';
			break;
		case OCFS2_LOCK_TYPE_OPEN:
			c = 'O';
			break;
		case OCFS2_LOCK_TYPE_FLOCK:
			c = 'F';
			break;
		case OCFS2_LOCK_TYPE_QINFO:
			c = 'Q';
			break;
		case OCFS2_LOCK_TYPE_NFS_SYNC:
			c = 'Y';
			break;
		case OCFS2_LOCK_TYPE_ORPHAN_SCAN:
			c = 'P';
			break;
		case OCFS2_LOCK_TYPE_REFCOUNT:
			c = 'T';
			break;
		case OCFS2_LOCK_TYPE_TRIM_FS:
			c = 'I';
			break;
		default:
			c = '\0';
	}

	return c;
}