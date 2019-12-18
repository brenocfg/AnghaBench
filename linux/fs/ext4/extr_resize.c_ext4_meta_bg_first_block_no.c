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
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  ext4_group_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_group_first_block_no (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_meta_bg_first_group (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ext4_fsblk_t ext4_meta_bg_first_block_no(struct super_block *sb,
					     ext4_group_t group) {
	group = ext4_meta_bg_first_group(sb, group);
	return ext4_group_first_block_no(sb, group);
}