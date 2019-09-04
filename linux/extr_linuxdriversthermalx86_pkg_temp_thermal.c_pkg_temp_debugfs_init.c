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
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debugfs ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_u32 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkg_interrupt_cnt ; 
 int /*<<< orphan*/  pkg_work_cnt ; 

__attribute__((used)) static int pkg_temp_debugfs_init(void)
{
	struct dentry *d;

	debugfs = debugfs_create_dir("pkg_temp_thermal", NULL);
	if (!debugfs)
		return -ENOENT;

	d = debugfs_create_u32("pkg_thres_interrupt", S_IRUGO, debugfs,
			       &pkg_interrupt_cnt);
	if (!d)
		goto err_out;

	d = debugfs_create_u32("pkg_thres_work", S_IRUGO, debugfs,
			       &pkg_work_cnt);
	if (!d)
		goto err_out;

	return 0;

err_out:
	debugfs_remove_recursive(debugfs);
	return -ENOENT;
}