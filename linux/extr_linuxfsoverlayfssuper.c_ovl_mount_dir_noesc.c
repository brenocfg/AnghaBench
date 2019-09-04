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
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 int /*<<< orphan*/  d_is_dir (int /*<<< orphan*/ ) ; 
 int kern_path (char const*,int /*<<< orphan*/ ,struct path*) ; 
 scalar_t__ ovl_dentry_weird (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_put_init (struct path*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int ovl_mount_dir_noesc(const char *name, struct path *path)
{
	int err = -EINVAL;

	if (!*name) {
		pr_err("overlayfs: empty lowerdir\n");
		goto out;
	}
	err = kern_path(name, LOOKUP_FOLLOW, path);
	if (err) {
		pr_err("overlayfs: failed to resolve '%s': %i\n", name, err);
		goto out;
	}
	err = -EINVAL;
	if (ovl_dentry_weird(path->dentry)) {
		pr_err("overlayfs: filesystem on '%s' not supported\n", name);
		goto out_put;
	}
	if (!d_is_dir(path->dentry)) {
		pr_err("overlayfs: '%s' not a directory\n", name);
		goto out_put;
	}
	return 0;

out_put:
	path_put_init(path);
out:
	return err;
}