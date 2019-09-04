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
struct f2fs_sb_info {int /*<<< orphan*/  s_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  __count_extent_cache (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_list_lock ; 
 int /*<<< orphan*/  f2fs_shrink_extent_tree (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void f2fs_leave_shrinker(struct f2fs_sb_info *sbi)
{
	f2fs_shrink_extent_tree(sbi, __count_extent_cache(sbi));

	spin_lock(&f2fs_list_lock);
	list_del_init(&sbi->s_list);
	spin_unlock(&f2fs_list_lock);
}