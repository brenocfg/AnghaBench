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
 int /*<<< orphan*/  debugfs_create_bool (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_fops ; 
 int /*<<< orphan*/  error_count ; 
 int /*<<< orphan*/  filter_fops ; 
 int /*<<< orphan*/  global_disable ; 
 int /*<<< orphan*/  min_free_entries ; 
 int /*<<< orphan*/  nr_total_entries ; 
 int /*<<< orphan*/  num_free_entries ; 
 int /*<<< orphan*/  show_all_errors ; 
 int /*<<< orphan*/  show_num_errors ; 

__attribute__((used)) static void dma_debug_fs_init(void)
{
	struct dentry *dentry = debugfs_create_dir("dma-api", NULL);

	debugfs_create_bool("disabled", 0444, dentry, &global_disable);
	debugfs_create_u32("error_count", 0444, dentry, &error_count);
	debugfs_create_u32("all_errors", 0644, dentry, &show_all_errors);
	debugfs_create_u32("num_errors", 0644, dentry, &show_num_errors);
	debugfs_create_u32("num_free_entries", 0444, dentry, &num_free_entries);
	debugfs_create_u32("min_free_entries", 0444, dentry, &min_free_entries);
	debugfs_create_u32("nr_total_entries", 0444, dentry, &nr_total_entries);
	debugfs_create_file("driver_filter", 0644, dentry, NULL, &filter_fops);
	debugfs_create_file("dump", 0444, dentry, NULL, &dump_fops);
}