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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct task_security_struct {int /*<<< orphan*/  sid; scalar_t__ create_sid; } ;
struct superblock_security_struct {int flags; scalar_t__ behavior; scalar_t__ mntpoint_sid; } ;
struct qstr {int dummy; } ;
struct inode_security_struct {int /*<<< orphan*/  sid; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {struct superblock_security_struct* s_security; } ;

/* Variables and functions */
 int SBLABEL_MNT ; 
 scalar_t__ SECURITY_FS_USE_MNTPOINT ; 
 int SE_SBINITIALIZED ; 
 struct inode_security_struct* inode_security (struct inode*) ; 
 int security_transition_sid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qstr const*,scalar_t__*) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int
selinux_determine_inode_label(const struct task_security_struct *tsec,
				 struct inode *dir,
				 const struct qstr *name, u16 tclass,
				 u32 *_new_isid)
{
	const struct superblock_security_struct *sbsec = dir->i_sb->s_security;

	if ((sbsec->flags & SE_SBINITIALIZED) &&
	    (sbsec->behavior == SECURITY_FS_USE_MNTPOINT)) {
		*_new_isid = sbsec->mntpoint_sid;
	} else if ((sbsec->flags & SBLABEL_MNT) &&
		   tsec->create_sid) {
		*_new_isid = tsec->create_sid;
	} else {
		const struct inode_security_struct *dsec = inode_security(dir);
		return security_transition_sid(&selinux_state, tsec->sid,
					       dsec->sid, tclass,
					       name, _new_isid);
	}

	return 0;
}