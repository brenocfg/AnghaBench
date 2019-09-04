#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  ext4_grpblk_t ;
typedef  int /*<<< orphan*/  ext4_group_t ;
struct TYPE_4__ {TYPE_1__* s_es; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_reserved_gdt_blocks; } ;

/* Variables and functions */
 TYPE_2__* EXT4_SB (struct super_block*) ; 
 scalar_t__ ext4_bg_has_super (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_bg_num_gdb (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ext4_grpblk_t ext4_group_overhead_blocks(struct super_block *sb,
						ext4_group_t group) {
	ext4_grpblk_t overhead;
	overhead = ext4_bg_num_gdb(sb, group);
	if (ext4_bg_has_super(sb, group))
		overhead += 1 +
			  le16_to_cpu(EXT4_SB(sb)->s_es->s_reserved_gdt_blocks);
	return overhead;
}