#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct fs_context {TYPE_2__* root; } ;
struct TYPE_4__ {TYPE_1__* d_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_umount; } ;

/* Variables and functions */
 struct vfsmount* ERR_PTR (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 struct vfsmount* vfs_create_mount (struct fs_context*) ; 
 int vfs_get_tree (struct fs_context*) ; 

struct vfsmount *fc_mount(struct fs_context *fc)
{
	int err = vfs_get_tree(fc);
	if (!err) {
		up_write(&fc->root->d_sb->s_umount);
		return vfs_create_mount(fc);
	}
	return ERR_PTR(err);
}