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
typedef  unsigned long ext4_group_t ;
struct TYPE_4__ {TYPE_1__* s_es; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_first_meta_bg; } ;

/* Variables and functions */
 unsigned long EXT4_DESC_PER_BLOCK (struct super_block*) ; 
 TYPE_2__* EXT4_SB (struct super_block*) ; 
 unsigned long ext4_bg_num_gdb_meta (struct super_block*,unsigned long) ; 
 unsigned long ext4_bg_num_gdb_nometa (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  ext4_has_feature_meta_bg (struct super_block*) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 

unsigned long ext4_bg_num_gdb(struct super_block *sb, ext4_group_t group)
{
	unsigned long first_meta_bg =
			le32_to_cpu(EXT4_SB(sb)->s_es->s_first_meta_bg);
	unsigned long metagroup = group / EXT4_DESC_PER_BLOCK(sb);

	if (!ext4_has_feature_meta_bg(sb) || metagroup < first_meta_bg)
		return ext4_bg_num_gdb_nometa(sb, group);

	return ext4_bg_num_gdb_meta(sb,group);

}