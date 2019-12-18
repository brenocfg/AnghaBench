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
typedef  scalar_t__ u64 ;
struct ocfs2_lock_res {int /*<<< orphan*/ * l_name; } ;
struct ocfs2_dentry_lock {struct ocfs2_lock_res dl_lockres; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_2__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int OCFS2_DENTRY_LOCK_INO_START ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_LOCK_TYPE_DENTRY ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocfs2_dentry_lops ; 
 int /*<<< orphan*/  ocfs2_lock_res_init_common (int /*<<< orphan*/ ,struct ocfs2_lock_res*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ocfs2_dentry_lock*) ; 
 int /*<<< orphan*/  ocfs2_lock_res_init_once (struct ocfs2_lock_res*) ; 
 int ocfs2_lock_type_char (int /*<<< orphan*/ ) ; 
 int snprintf (int /*<<< orphan*/ *,int,char*,int,long long) ; 

void ocfs2_dentry_lock_res_init(struct ocfs2_dentry_lock *dl,
				u64 parent, struct inode *inode)
{
	int len;
	u64 inode_blkno = OCFS2_I(inode)->ip_blkno;
	__be64 inode_blkno_be = cpu_to_be64(inode_blkno);
	struct ocfs2_lock_res *lockres = &dl->dl_lockres;

	ocfs2_lock_res_init_once(lockres);

	/*
	 * Unfortunately, the standard lock naming scheme won't work
	 * here because we have two 16 byte values to use. Instead,
	 * we'll stuff the inode number as a binary value. We still
	 * want error prints to show something without garbling the
	 * display, so drop a null byte in there before the inode
	 * number. A future version of OCFS2 will likely use all
	 * binary lock names. The stringified names have been a
	 * tremendous aid in debugging, but now that the debugfs
	 * interface exists, we can mangle things there if need be.
	 *
	 * NOTE: We also drop the standard "pad" value (the total lock
	 * name size stays the same though - the last part is all
	 * zeros due to the memset in ocfs2_lock_res_init_once()
	 */
	len = snprintf(lockres->l_name, OCFS2_DENTRY_LOCK_INO_START,
		       "%c%016llx",
		       ocfs2_lock_type_char(OCFS2_LOCK_TYPE_DENTRY),
		       (long long)parent);

	BUG_ON(len != (OCFS2_DENTRY_LOCK_INO_START - 1));

	memcpy(&lockres->l_name[OCFS2_DENTRY_LOCK_INO_START], &inode_blkno_be,
	       sizeof(__be64));

	ocfs2_lock_res_init_common(OCFS2_SB(inode->i_sb), lockres,
				   OCFS2_LOCK_TYPE_DENTRY, &ocfs2_dentry_lops,
				   dl);
}