#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct ext4_inode_info {scalar_t__* i_data; } ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;
typedef  scalar_t__ __le32 ;
struct TYPE_5__ {TYPE_1__* bh; scalar_t__* p; } ;
struct TYPE_4__ {int /*<<< orphan*/  b_blocknr; scalar_t__ b_data; } ;
typedef  TYPE_2__ Indirect ;

/* Variables and functions */
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  ext4_inode_to_goal_block (struct inode*) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 

__attribute__((used)) static ext4_fsblk_t ext4_find_near(struct inode *inode, Indirect *ind)
{
	struct ext4_inode_info *ei = EXT4_I(inode);
	__le32 *start = ind->bh ? (__le32 *) ind->bh->b_data : ei->i_data;
	__le32 *p;

	/* Try to find previous block */
	for (p = ind->p - 1; p >= start; p--) {
		if (*p)
			return le32_to_cpu(*p);
	}

	/* No such thing, so let's try location of indirect block */
	if (ind->bh)
		return ind->bh->b_blocknr;

	/*
	 * It is going to be referred to from the inode itself? OK, just put it
	 * into the same cylinder group then.
	 */
	return ext4_inode_to_goal_block(inode);
}