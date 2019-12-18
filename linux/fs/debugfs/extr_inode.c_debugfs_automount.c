#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct path {TYPE_1__* dentry; } ;
typedef  struct vfsmount* (* debugfs_automount_t ) (TYPE_1__*,int /*<<< orphan*/ ) ;
struct TYPE_5__ {int /*<<< orphan*/  i_private; } ;
struct TYPE_4__ {scalar_t__ d_fsdata; } ;

/* Variables and functions */
 TYPE_2__* d_inode (TYPE_1__*) ; 

__attribute__((used)) static struct vfsmount *debugfs_automount(struct path *path)
{
	debugfs_automount_t f;
	f = (debugfs_automount_t)path->dentry->d_fsdata;
	return f(path->dentry, d_inode(path->dentry)->i_private);
}