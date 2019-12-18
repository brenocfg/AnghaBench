#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  k_objectid; int /*<<< orphan*/  k_dir_id; } ;

/* Variables and functions */
 TYPE_1__* INODE_PKEY (struct inode*) ; 
 scalar_t__ TEST_OPTION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ block_group_used (int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packing_groups ; 

__le32 reiserfs_choose_packing(struct inode * dir)
{
	__le32 packing;
	if (TEST_OPTION(packing_groups, dir->i_sb)) {
		u32 parent_dir = le32_to_cpu(INODE_PKEY(dir)->k_dir_id);
		/*
		 * some versions of reiserfsck expect packing locality 1 to be
		 * special
		 */
		if (parent_dir == 1 || block_group_used(dir->i_sb, parent_dir))
			packing = INODE_PKEY(dir)->k_objectid;
		else
			packing = INODE_PKEY(dir)->k_dir_id;
	} else
		packing = INODE_PKEY(dir)->k_objectid;
	return packing;
}