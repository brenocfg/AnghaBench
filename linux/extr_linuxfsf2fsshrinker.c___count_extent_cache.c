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
struct f2fs_sb_info {int /*<<< orphan*/  total_ext_node; int /*<<< orphan*/  total_zombie_tree; } ;

/* Variables and functions */
 unsigned long atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long __count_extent_cache(struct f2fs_sb_info *sbi)
{
	return atomic_read(&sbi->total_zombie_tree) +
				atomic_read(&sbi->total_ext_node);
}