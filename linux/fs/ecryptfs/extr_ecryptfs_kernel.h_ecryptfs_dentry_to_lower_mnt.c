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
struct vfsmount {int dummy; } ;
struct TYPE_2__ {struct vfsmount* mnt; } ;
struct ecryptfs_dentry_info {TYPE_1__ lower_path; } ;
struct dentry {scalar_t__ d_fsdata; } ;

/* Variables and functions */

__attribute__((used)) static inline struct vfsmount *
ecryptfs_dentry_to_lower_mnt(struct dentry *dentry)
{
	return ((struct ecryptfs_dentry_info *)dentry->d_fsdata)->lower_path.mnt;
}