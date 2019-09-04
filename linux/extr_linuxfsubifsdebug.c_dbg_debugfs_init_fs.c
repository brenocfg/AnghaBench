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
struct TYPE_2__ {int /*<<< orphan*/  vol_id; int /*<<< orphan*/  ubi_num; } ;
struct ubifs_info {TYPE_1__ vi; struct ubifs_debug_info* dbg; } ;
struct ubifs_debug_info {char* dfs_dir_name; struct dentry* dfs_dir; struct dentry* dfs_ro_error; struct dentry* dfs_tst_rcvry; struct dentry* dfs_chk_fs; struct dentry* dfs_chk_lprops; struct dentry* dfs_chk_orph; struct dentry* dfs_chk_index; struct dentry* dfs_chk_gen; struct dentry* dfs_dump_tnc; struct dentry* dfs_dump_budg; struct dentry* dfs_dump_lprops; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DEBUG_FS ; 
 int /*<<< orphan*/  EINVAL ; 
 int ENODEV ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int UBIFS_DFS_DIR_LEN ; 
 char* UBIFS_DFS_DIR_NAME ; 
 struct dentry* debugfs_create_dir (char const*,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (char const*,int,struct dentry*,struct ubifs_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 int /*<<< orphan*/  dfs_fops ; 
 int /*<<< orphan*/  dfs_rootdir ; 
 int snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,char const*,int) ; 

int dbg_debugfs_init_fs(struct ubifs_info *c)
{
	int err, n;
	const char *fname;
	struct dentry *dent;
	struct ubifs_debug_info *d = c->dbg;

	if (!IS_ENABLED(CONFIG_DEBUG_FS))
		return 0;

	n = snprintf(d->dfs_dir_name, UBIFS_DFS_DIR_LEN + 1, UBIFS_DFS_DIR_NAME,
		     c->vi.ubi_num, c->vi.vol_id);
	if (n == UBIFS_DFS_DIR_LEN) {
		/* The array size is too small */
		fname = UBIFS_DFS_DIR_NAME;
		dent = ERR_PTR(-EINVAL);
		goto out;
	}

	fname = d->dfs_dir_name;
	dent = debugfs_create_dir(fname, dfs_rootdir);
	if (IS_ERR_OR_NULL(dent))
		goto out;
	d->dfs_dir = dent;

	fname = "dump_lprops";
	dent = debugfs_create_file(fname, S_IWUSR, d->dfs_dir, c, &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_dump_lprops = dent;

	fname = "dump_budg";
	dent = debugfs_create_file(fname, S_IWUSR, d->dfs_dir, c, &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_dump_budg = dent;

	fname = "dump_tnc";
	dent = debugfs_create_file(fname, S_IWUSR, d->dfs_dir, c, &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_dump_tnc = dent;

	fname = "chk_general";
	dent = debugfs_create_file(fname, S_IRUSR | S_IWUSR, d->dfs_dir, c,
				   &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_chk_gen = dent;

	fname = "chk_index";
	dent = debugfs_create_file(fname, S_IRUSR | S_IWUSR, d->dfs_dir, c,
				   &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_chk_index = dent;

	fname = "chk_orphans";
	dent = debugfs_create_file(fname, S_IRUSR | S_IWUSR, d->dfs_dir, c,
				   &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_chk_orph = dent;

	fname = "chk_lprops";
	dent = debugfs_create_file(fname, S_IRUSR | S_IWUSR, d->dfs_dir, c,
				   &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_chk_lprops = dent;

	fname = "chk_fs";
	dent = debugfs_create_file(fname, S_IRUSR | S_IWUSR, d->dfs_dir, c,
				   &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_chk_fs = dent;

	fname = "tst_recovery";
	dent = debugfs_create_file(fname, S_IRUSR | S_IWUSR, d->dfs_dir, c,
				   &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_tst_rcvry = dent;

	fname = "ro_error";
	dent = debugfs_create_file(fname, S_IRUSR | S_IWUSR, d->dfs_dir, c,
				   &dfs_fops);
	if (IS_ERR_OR_NULL(dent))
		goto out_remove;
	d->dfs_ro_error = dent;

	return 0;

out_remove:
	debugfs_remove_recursive(d->dfs_dir);
out:
	err = dent ? PTR_ERR(dent) : -ENODEV;
	ubifs_err(c, "cannot create \"%s\" debugfs file or directory, error %d\n",
		  fname, err);
	return err;
}