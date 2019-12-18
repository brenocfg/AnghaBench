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
struct smack_known {int dummy; } ;
struct inode_smack {struct smack_known* smk_mmap; struct smack_known* smk_task; struct smack_known* smk_inode; int /*<<< orphan*/  smk_flags; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct smack_known*) ; 
 int /*<<< orphan*/  SMK_INODE_TRANSMUTE ; 
 int /*<<< orphan*/  XATTR_NAME_SMACK ; 
 int /*<<< orphan*/  XATTR_NAME_SMACKEXEC ; 
 int /*<<< orphan*/  XATTR_NAME_SMACKMMAP ; 
 int /*<<< orphan*/  XATTR_NAME_SMACKTRANSMUTE ; 
 int /*<<< orphan*/  d_backing_inode (struct dentry*) ; 
 struct inode_smack* smack_inode (int /*<<< orphan*/ ) ; 
 struct smack_known* smk_import_entry (void const*,size_t) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smack_inode_post_setxattr(struct dentry *dentry, const char *name,
				      const void *value, size_t size, int flags)
{
	struct smack_known *skp;
	struct inode_smack *isp = smack_inode(d_backing_inode(dentry));

	if (strcmp(name, XATTR_NAME_SMACKTRANSMUTE) == 0) {
		isp->smk_flags |= SMK_INODE_TRANSMUTE;
		return;
	}

	if (strcmp(name, XATTR_NAME_SMACK) == 0) {
		skp = smk_import_entry(value, size);
		if (!IS_ERR(skp))
			isp->smk_inode = skp;
	} else if (strcmp(name, XATTR_NAME_SMACKEXEC) == 0) {
		skp = smk_import_entry(value, size);
		if (!IS_ERR(skp))
			isp->smk_task = skp;
	} else if (strcmp(name, XATTR_NAME_SMACKMMAP) == 0) {
		skp = smk_import_entry(value, size);
		if (!IS_ERR(skp))
			isp->smk_mmap = skp;
	}

	return;
}