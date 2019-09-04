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
struct path {int /*<<< orphan*/  dentry; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ovl_dentry_remote (int /*<<< orphan*/ ) ; 
 int ovl_mount_dir_noesc (char*,struct path*) ; 
 int /*<<< orphan*/  ovl_unescape (char*) ; 
 int /*<<< orphan*/  path_put_init (struct path*) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 

__attribute__((used)) static int ovl_mount_dir(const char *name, struct path *path)
{
	int err = -ENOMEM;
	char *tmp = kstrdup(name, GFP_KERNEL);

	if (tmp) {
		ovl_unescape(tmp);
		err = ovl_mount_dir_noesc(tmp, path);

		if (!err)
			if (ovl_dentry_remote(path->dentry)) {
				pr_err("overlayfs: filesystem on '%s' not supported as upperdir\n",
				       tmp);
				path_put_init(path);
				err = -EINVAL;
			}
		kfree(tmp);
	}
	return err;
}