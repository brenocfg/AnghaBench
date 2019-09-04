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
struct vfsmount {int dummy; } ;
struct nfs_server {int dummy; } ;
struct nfs_clone_mount {int /*<<< orphan*/  dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_xdev_fs_type ; 
 struct vfsmount* vfs_submount (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,struct nfs_clone_mount*) ; 

__attribute__((used)) static struct vfsmount *nfs_do_clone_mount(struct nfs_server *server,
					   const char *devname,
					   struct nfs_clone_mount *mountdata)
{
	return vfs_submount(mountdata->dentry, &nfs_xdev_fs_type, devname, mountdata);
}