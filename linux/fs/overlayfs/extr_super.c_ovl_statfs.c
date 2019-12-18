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
struct path {int dummy; } ;
struct ovl_fs {int /*<<< orphan*/  namelen; } ;
struct kstatfs {int /*<<< orphan*/  f_type; int /*<<< orphan*/  f_namelen; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {struct dentry* s_root; struct ovl_fs* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVERLAYFS_SUPER_MAGIC ; 
 int /*<<< orphan*/  ovl_path_real (struct dentry*,struct path*) ; 
 int vfs_statfs (struct path*,struct kstatfs*) ; 

__attribute__((used)) static int ovl_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct ovl_fs *ofs = dentry->d_sb->s_fs_info;
	struct dentry *root_dentry = dentry->d_sb->s_root;
	struct path path;
	int err;

	ovl_path_real(root_dentry, &path);

	err = vfs_statfs(&path, buf);
	if (!err) {
		buf->f_namelen = ofs->namelen;
		buf->f_type = OVERLAYFS_SUPER_MAGIC;
	}

	return err;
}