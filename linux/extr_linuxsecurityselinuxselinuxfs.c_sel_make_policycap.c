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
struct selinux_fs_info {int /*<<< orphan*/  sb; int /*<<< orphan*/  policycap_dir; } ;
struct inode {unsigned int i_ino; int /*<<< orphan*/ * i_fop; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char**) ; 
 int ENOMEM ; 
 unsigned int POLICYDB_CAPABILITY_MAX ; 
 unsigned int SEL_POLICYCAP_INO_OFFSET ; 
 int S_IFREG ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct inode* sel_make_inode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sel_policycap_ops ; 
 int /*<<< orphan*/  sel_remove_entries (int /*<<< orphan*/ ) ; 
 char** selinux_policycap_names ; 

__attribute__((used)) static int sel_make_policycap(struct selinux_fs_info *fsi)
{
	unsigned int iter;
	struct dentry *dentry = NULL;
	struct inode *inode = NULL;

	sel_remove_entries(fsi->policycap_dir);

	for (iter = 0; iter <= POLICYDB_CAPABILITY_MAX; iter++) {
		if (iter < ARRAY_SIZE(selinux_policycap_names))
			dentry = d_alloc_name(fsi->policycap_dir,
					      selinux_policycap_names[iter]);
		else
			dentry = d_alloc_name(fsi->policycap_dir, "unknown");

		if (dentry == NULL)
			return -ENOMEM;

		inode = sel_make_inode(fsi->sb, S_IFREG | 0444);
		if (inode == NULL) {
			dput(dentry);
			return -ENOMEM;
		}

		inode->i_fop = &sel_policycap_ops;
		inode->i_ino = iter | SEL_POLICYCAP_INO_OFFSET;
		d_add(dentry, inode);
	}

	return 0;
}