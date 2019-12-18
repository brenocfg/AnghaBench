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
typedef  int u32 ;
struct super_block {int dummy; } ;
struct hfsplus_sb_info {TYPE_2__* s_vhdr; } ;
struct hfs_btree {scalar_t__ cnid; TYPE_1__* inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  attributes; } ;
struct TYPE_3__ {struct super_block* i_sb; } ;

/* Variables and functions */
 scalar_t__ HFSPLUS_CAT_CNID ; 
 struct hfsplus_sb_info* HFSPLUS_SB (struct super_block*) ; 
 int const HFSPLUS_VOL_UNUSED_NODE_FIX ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

bool hfs_bnode_need_zeroout(struct hfs_btree *tree)
{
	struct super_block *sb = tree->inode->i_sb;
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	const u32 volume_attr = be32_to_cpu(sbi->s_vhdr->attributes);

	return tree->cnid == HFSPLUS_CAT_CNID &&
		volume_attr & HFSPLUS_VOL_UNUSED_NODE_FIX;
}