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
struct super_block {int dummy; } ;
struct kernfs_syscall_ops {int (* remount_fs ) (struct kernfs_root*,int*,char*) ;} ;
struct kernfs_root {struct kernfs_syscall_ops* syscall_ops; } ;
struct TYPE_2__ {struct kernfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* kernfs_info (struct super_block*) ; 
 int stub1 (struct kernfs_root*,int*,char*) ; 

__attribute__((used)) static int kernfs_sop_remount_fs(struct super_block *sb, int *flags, char *data)
{
	struct kernfs_root *root = kernfs_info(sb)->root;
	struct kernfs_syscall_ops *scops = root->syscall_ops;

	if (scops && scops->remount_fs)
		return scops->remount_fs(root, flags, data);
	return 0;
}