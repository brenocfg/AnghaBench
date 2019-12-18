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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  ovl_copyattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dentry* ovl_dentry_upper (struct dentry*) ; 
 int /*<<< orphan*/  ovl_dentry_version_inc (struct dentry*,int) ; 

void ovl_dir_modified(struct dentry *dentry, bool impurity)
{
	/* Copy mtime/ctime */
	ovl_copyattr(d_inode(ovl_dentry_upper(dentry)), d_inode(dentry));

	ovl_dentry_version_inc(dentry, impurity);
}