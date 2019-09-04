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
struct inode {TYPE_1__* i_sb; } ;
struct iattr {unsigned int ia_valid; } ;
struct dentry {int dummy; } ;
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {scalar_t__ s_magic; } ;

/* Variables and functions */
 unsigned int ATTR_ATIME_SET ; 
 unsigned int ATTR_FILE ; 
 unsigned int ATTR_FORCE ; 
 unsigned int ATTR_GID ; 
 unsigned int ATTR_KILL_SGID ; 
 unsigned int ATTR_KILL_SUID ; 
 unsigned int ATTR_MODE ; 
 unsigned int ATTR_MTIME_SET ; 
 unsigned int ATTR_SIZE ; 
 unsigned int ATTR_TIMES_SET ; 
 unsigned int ATTR_UID ; 
 int /*<<< orphan*/  FILE__OPEN ; 
 int /*<<< orphan*/  FILE__SETATTR ; 
 int /*<<< orphan*/  FILE__WRITE ; 
 scalar_t__ SOCKFS_MAGIC ; 
 struct cred* current_cred () ; 
 struct inode* d_backing_inode (struct dentry*) ; 
 int dentry_has_perm (struct cred const*,struct dentry*,int /*<<< orphan*/ ) ; 
 scalar_t__ selinux_policycap_openperm () ; 

__attribute__((used)) static int selinux_inode_setattr(struct dentry *dentry, struct iattr *iattr)
{
	const struct cred *cred = current_cred();
	struct inode *inode = d_backing_inode(dentry);
	unsigned int ia_valid = iattr->ia_valid;
	__u32 av = FILE__WRITE;

	/* ATTR_FORCE is just used for ATTR_KILL_S[UG]ID. */
	if (ia_valid & ATTR_FORCE) {
		ia_valid &= ~(ATTR_KILL_SUID | ATTR_KILL_SGID | ATTR_MODE |
			      ATTR_FORCE);
		if (!ia_valid)
			return 0;
	}

	if (ia_valid & (ATTR_MODE | ATTR_UID | ATTR_GID |
			ATTR_ATIME_SET | ATTR_MTIME_SET | ATTR_TIMES_SET))
		return dentry_has_perm(cred, dentry, FILE__SETATTR);

	if (selinux_policycap_openperm() &&
	    inode->i_sb->s_magic != SOCKFS_MAGIC &&
	    (ia_valid & ATTR_SIZE) &&
	    !(ia_valid & ATTR_FILE))
		av |= FILE__OPEN;

	return dentry_has_perm(cred, dentry, av);
}