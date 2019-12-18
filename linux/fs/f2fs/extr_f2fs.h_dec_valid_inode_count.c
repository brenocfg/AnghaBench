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
struct f2fs_sb_info {int /*<<< orphan*/  total_valid_inode_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  percpu_counter_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void dec_valid_inode_count(struct f2fs_sb_info *sbi)
{
	percpu_counter_dec(&sbi->total_valid_inode_count);
}