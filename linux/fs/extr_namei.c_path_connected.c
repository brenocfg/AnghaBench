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
struct vfsmount {scalar_t__ mnt_root; struct super_block* mnt_sb; } ;
struct super_block {int s_iflags; scalar_t__ s_root; } ;
struct path {int /*<<< orphan*/  dentry; struct vfsmount* mnt; } ;

/* Variables and functions */
 int SB_I_MULTIROOT ; 
 int is_subdir (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool path_connected(const struct path *path)
{
	struct vfsmount *mnt = path->mnt;
	struct super_block *sb = mnt->mnt_sb;

	/* Bind mounts and multi-root filesystems can have disconnected paths */
	if (!(sb->s_iflags & SB_I_MULTIROOT) && (mnt->mnt_root == sb->s_root))
		return true;

	return is_subdir(path->dentry, mnt->mnt_root);
}