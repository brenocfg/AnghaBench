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

/* Variables and functions */
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  debugfs_create_dir (char const*,int /*<<< orphan*/ *) ; 
 void* debugfs_create_file (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* dfs_chk_fs ; 
 void* dfs_chk_gen ; 
 void* dfs_chk_index ; 
 void* dfs_chk_lprops ; 
 void* dfs_chk_orph ; 
 int /*<<< orphan*/  dfs_global_fops ; 
 int /*<<< orphan*/  dfs_rootdir ; 
 void* dfs_tst_rcvry ; 

void dbg_debugfs_init(void)
{
	const char *fname;

	fname = "ubifs";
	dfs_rootdir = debugfs_create_dir(fname, NULL);

	fname = "chk_general";
	dfs_chk_gen = debugfs_create_file(fname, S_IRUSR | S_IWUSR, dfs_rootdir,
					  NULL, &dfs_global_fops);

	fname = "chk_index";
	dfs_chk_index = debugfs_create_file(fname, S_IRUSR | S_IWUSR,
					    dfs_rootdir, NULL, &dfs_global_fops);

	fname = "chk_orphans";
	dfs_chk_orph = debugfs_create_file(fname, S_IRUSR | S_IWUSR,
					   dfs_rootdir, NULL, &dfs_global_fops);

	fname = "chk_lprops";
	dfs_chk_lprops = debugfs_create_file(fname, S_IRUSR | S_IWUSR,
					     dfs_rootdir, NULL, &dfs_global_fops);

	fname = "chk_fs";
	dfs_chk_fs = debugfs_create_file(fname, S_IRUSR | S_IWUSR, dfs_rootdir,
					 NULL, &dfs_global_fops);

	fname = "tst_recovery";
	dfs_tst_rcvry = debugfs_create_file(fname, S_IRUSR | S_IWUSR,
					    dfs_rootdir, NULL, &dfs_global_fops);
}