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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,struct dentry*,struct dentry*,int) ; 
 int vfs_rename (struct inode*,struct dentry*,struct inode*,struct dentry*,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline int ovl_do_rename(struct inode *olddir, struct dentry *olddentry,
				struct inode *newdir, struct dentry *newdentry,
				unsigned int flags)
{
	int err;

	pr_debug("rename(%pd2, %pd2, 0x%x)\n", olddentry, newdentry, flags);
	err = vfs_rename(olddir, olddentry, newdir, newdentry, NULL, flags);
	if (err) {
		pr_debug("...rename(%pd2, %pd2, ...) = %i\n",
			 olddentry, newdentry, err);
	}
	return err;
}