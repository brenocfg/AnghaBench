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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fdatawrite_one_bdev ; 
 int /*<<< orphan*/  iterate_bdevs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iterate_supers (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  kfree (struct work_struct*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  sync_fs_one_sb ; 
 int /*<<< orphan*/  sync_inodes_one_sb ; 

__attribute__((used)) static void do_sync_work(struct work_struct *work)
{
	int nowait = 0;

	/*
	 * Sync twice to reduce the possibility we skipped some inodes / pages
	 * because they were temporarily locked
	 */
	iterate_supers(sync_inodes_one_sb, &nowait);
	iterate_supers(sync_fs_one_sb, &nowait);
	iterate_bdevs(fdatawrite_one_bdev, NULL);
	iterate_supers(sync_inodes_one_sb, &nowait);
	iterate_supers(sync_fs_one_sb, &nowait);
	iterate_bdevs(fdatawrite_one_bdev, NULL);
	printk("Emergency Sync complete\n");
	kfree(work);
}