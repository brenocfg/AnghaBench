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
struct inode {int dummy; } ;
typedef  scalar_t__ __u64 ;
struct TYPE_4__ {int /*<<< orphan*/  i_bmap; } ;
struct TYPE_3__ {int /*<<< orphan*/  mi_blocks_per_desc_block; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_2__* NILFS_I (struct inode*) ; 
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 scalar_t__ likely (int) ; 
 int nilfs_bmap_last_key (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int nilfs_palloc_count_desc_blocks(struct inode *inode,
					    unsigned long *desc_blocks)
{
	__u64 blknum;
	int ret;

	ret = nilfs_bmap_last_key(NILFS_I(inode)->i_bmap, &blknum);
	if (likely(!ret))
		*desc_blocks = DIV_ROUND_UP(
			(unsigned long)blknum,
			NILFS_MDT(inode)->mi_blocks_per_desc_block);
	return ret;
}