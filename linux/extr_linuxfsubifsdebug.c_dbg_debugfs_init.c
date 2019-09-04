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
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DEBUG_FS ; 
 int ENODEV ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 TYPE_1__* current ; 
 struct dentry* debugfs_create_dir (char const*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_file (char const*,int,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 struct dentry* dfs_chk_fs ; 
 struct dentry* dfs_chk_gen ; 
 struct dentry* dfs_chk_index ; 
 struct dentry* dfs_chk_lprops ; 
 struct dentry* dfs_chk_orph ; 
 int /*<<< orphan*/  dfs_global_fops ; 
 struct dentry* dfs_rootdir ; 
 struct dentry* dfs_tst_rcvry ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,char const*,int) ; 

int dbg_debugfs_init(void)
{
	int err;
	const char *fname;
	struct dentry *dent;

	if (!IS_ENABLED(CONFIG_DEBUG_FS))
		return 0;

	fname = "ubifs";
	dent = debugfs_create_dir(fname, NULL);
	if (IS_ERR_OR_NULL(dent))
		goto out;
	dfs_rootdir = dent;

	fname = "chk_general";
	dent = debugfs_create_file(fname, S_IRUSR | S_IWUSR, dfs_rootdir, NULL,
				   &dfs_global_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	dfs_chk_gen = dent;

	fname = "chk_index";
	dent = debugfs_create_file(fname, S_IRUSR | S_IWUSR, dfs_rootdir, NULL,
				   &dfs_global_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	dfs_chk_index = dent;

	fname = "chk_orphans";
	dent = debugfs_create_file(fname, S_IRUSR | S_IWUSR, dfs_rootdir, NULL,
				   &dfs_global_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	dfs_chk_orph = dent;

	fname = "chk_lprops";
	dent = debugfs_create_file(fname, S_IRUSR | S_IWUSR, dfs_rootdir, NULL,
				   &dfs_global_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	dfs_chk_lprops = dent;

	fname = "chk_fs";
	dent = debugfs_create_file(fname, S_IRUSR | S_IWUSR, dfs_rootdir, NULL,
				   &dfs_global_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	dfs_chk_fs = dent;

	fname = "tst_recovery";
	dent = debugfs_create_file(fname, S_IRUSR | S_IWUSR, dfs_rootdir, NULL,
				   &dfs_global_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	dfs_tst_rcvry = dent;

	return 0;

out_remove:
	debugfs_remove_recursive(dfs_rootdir);
out:
	err = dent ? PTR_ERR(dent) : -ENODEV;
	pr_err("UBIFS error (pid %d): cannot create \"%s\" debugfs file or directory, error %d\n",
	       current->pid, fname, err);
	return err;
}