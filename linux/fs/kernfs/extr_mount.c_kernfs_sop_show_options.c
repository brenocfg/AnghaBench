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
struct seq_file {int dummy; } ;
struct kernfs_syscall_ops {int (* show_options ) (struct seq_file*,struct kernfs_root*) ;} ;
struct kernfs_root {struct kernfs_syscall_ops* syscall_ops; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kernfs_dentry_node (struct dentry*) ; 
 struct kernfs_root* kernfs_root (int /*<<< orphan*/ ) ; 
 int stub1 (struct seq_file*,struct kernfs_root*) ; 

__attribute__((used)) static int kernfs_sop_show_options(struct seq_file *sf, struct dentry *dentry)
{
	struct kernfs_root *root = kernfs_root(kernfs_dentry_node(dentry));
	struct kernfs_syscall_ops *scops = root->syscall_ops;

	if (scops && scops->show_options)
		return scops->show_options(sf, root);
	return 0;
}