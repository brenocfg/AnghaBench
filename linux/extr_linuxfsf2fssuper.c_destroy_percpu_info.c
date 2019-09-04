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
struct f2fs_sb_info {int /*<<< orphan*/  total_valid_inode_count; int /*<<< orphan*/  alloc_valid_block_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  percpu_counter_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_percpu_info(struct f2fs_sb_info *sbi)
{
	percpu_counter_destroy(&sbi->alloc_valid_block_count);
	percpu_counter_destroy(&sbi->total_valid_inode_count);
}