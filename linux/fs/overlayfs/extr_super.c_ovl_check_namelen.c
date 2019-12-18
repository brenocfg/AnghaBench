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
struct path {int dummy; } ;
struct ovl_fs {int /*<<< orphan*/  namelen; } ;
struct kstatfs {int /*<<< orphan*/  f_namelen; } ;

/* Variables and functions */
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int vfs_statfs (struct path*,struct kstatfs*) ; 

__attribute__((used)) static int ovl_check_namelen(struct path *path, struct ovl_fs *ofs,
			     const char *name)
{
	struct kstatfs statfs;
	int err = vfs_statfs(path, &statfs);

	if (err)
		pr_err("overlayfs: statfs failed on '%s'\n", name);
	else
		ofs->namelen = max(ofs->namelen, statfs.f_namelen);

	return err;
}