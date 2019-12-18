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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,struct dentry*,int /*<<< orphan*/ ,int) ; 
 int vfs_mkdir (struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ovl_do_mkdir(struct inode *dir, struct dentry *dentry,
			       umode_t mode)
{
	int err = vfs_mkdir(dir, dentry, mode);
	pr_debug("mkdir(%pd2, 0%o) = %i\n", dentry, mode, err);
	return err;
}