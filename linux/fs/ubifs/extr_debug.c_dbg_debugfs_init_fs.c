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
struct ubifs_debug_info {char* dfs_dir_name; int /*<<< orphan*/  dfs_dir; void* dfs_ro_error; void* dfs_tst_rcvry; void* dfs_chk_fs; void* dfs_chk_lprops; void* dfs_chk_orph; void* dfs_chk_index; void* dfs_chk_gen; void* dfs_dump_tnc; void* dfs_dump_budg; void* dfs_dump_lprops; } ;

/* Variables and functions */
 int S_IRUSR ; 
 int S_IWUSR ; 
 int UBIFS_DFS_DIR_LEN ; 
 char* UBIFS_DFS_DIR_NAME ; 
 int /*<<< orphan*/  debugfs_create_dir (char const*,int /*<<< orphan*/ ) ; 
 void* debugfs_create_file (char const*,int,int /*<<< orphan*/ ,struct ubifs_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dfs_fops ; 
 int /*<<< orphan*/  dfs_rootdir ; 
 int snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dbg_debugfs_init_fs(struct ubifs_info *c)
{
	int n;
	const char *fname;
	struct ubifs_debug_info *d = c->dbg;

	n = snprintf(d->dfs_dir_name, UBIFS_DFS_DIR_LEN + 1, UBIFS_DFS_DIR_NAME,
		     c->vi.ubi_num, c->vi.vol_id);
	if (n == UBIFS_DFS_DIR_LEN) {
		/* The array size is too small */
		return;
	}

	fname = d->dfs_dir_name;
	d->dfs_dir = debugfs_create_dir(fname, dfs_rootdir);

	fname = "dump_lprops";
	d->dfs_dump_lprops = debugfs_create_file(fname, S_IWUSR, d->dfs_dir, c,
						 &dfs_fops);

	fname = "dump_budg";
	d->dfs_dump_budg = debugfs_create_file(fname, S_IWUSR, d->dfs_dir, c,
					       &dfs_fops);

	fname = "dump_tnc";
	d->dfs_dump_tnc = debugfs_create_file(fname, S_IWUSR, d->dfs_dir, c,
					      &dfs_fops);

	fname = "chk_general";
	d->dfs_chk_gen = debugfs_create_file(fname, S_IRUSR | S_IWUSR,
					     d->dfs_dir, c, &dfs_fops);

	fname = "chk_index";
	d->dfs_chk_index = debugfs_create_file(fname, S_IRUSR | S_IWUSR,
					       d->dfs_dir, c, &dfs_fops);

	fname = "chk_orphans";
	d->dfs_chk_orph = debugfs_create_file(fname, S_IRUSR | S_IWUSR,
					      d->dfs_dir, c, &dfs_fops);

	fname = "chk_lprops";
	d->dfs_chk_lprops = debugfs_create_file(fname, S_IRUSR | S_IWUSR,
						d->dfs_dir, c, &dfs_fops);

	fname = "chk_fs";
	d->dfs_chk_fs = debugfs_create_file(fname, S_IRUSR | S_IWUSR,
					    d->dfs_dir, c, &dfs_fops);

	fname = "tst_recovery";
	d->dfs_tst_rcvry = debugfs_create_file(fname, S_IRUSR | S_IWUSR,
					       d->dfs_dir, c, &dfs_fops);

	fname = "ro_error";
	d->dfs_ro_error = debugfs_create_file(fname, S_IRUSR | S_IWUSR,
					      d->dfs_dir, c, &dfs_fops);
}