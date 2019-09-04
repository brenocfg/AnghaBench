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
struct udf_inode_info {scalar_t__ i_next_alloc_block; int /*<<< orphan*/  i_data_sem; int /*<<< orphan*/  i_next_alloc_goal; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int EIO ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ inode_getblk (struct inode*,scalar_t__,int*,int*) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_buffer_new (struct buffer_head*) ; 
 scalar_t__ udf_block_map (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  udf_clear_extent_cache (struct inode*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int udf_get_block(struct inode *inode, sector_t block,
			 struct buffer_head *bh_result, int create)
{
	int err, new;
	sector_t phys = 0;
	struct udf_inode_info *iinfo;

	if (!create) {
		phys = udf_block_map(inode, block);
		if (phys)
			map_bh(bh_result, inode->i_sb, phys);
		return 0;
	}

	err = -EIO;
	new = 0;
	iinfo = UDF_I(inode);

	down_write(&iinfo->i_data_sem);
	if (block == iinfo->i_next_alloc_block + 1) {
		iinfo->i_next_alloc_block++;
		iinfo->i_next_alloc_goal++;
	}

	udf_clear_extent_cache(inode);
	phys = inode_getblk(inode, block, &err, &new);
	if (!phys)
		goto abort;

	if (new)
		set_buffer_new(bh_result);
	map_bh(bh_result, inode->i_sb, phys);

abort:
	up_write(&iinfo->i_data_sem);
	return err;
}