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
struct inode {int i_ino; TYPE_1__* i_sb; } ;
typedef  int ext4_fsblk_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_priv; } ;
typedef  int /*<<< orphan*/  PEXT2_VCB ;

/* Variables and functions */
 int BLOCKS_PER_GROUP ; 

__attribute__((used)) static inline ext4_fsblk_t ext4_inode_to_goal_block(struct inode *inode)
{
	PEXT2_VCB Vcb;
	Vcb = inode->i_sb->s_priv;
	return (inode->i_ino - 1) / BLOCKS_PER_GROUP;
}