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
struct inode {int dummy; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_unwritten; } ;

/* Variables and functions */
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_STATE_DIO_UNWRITTEN ; 
 unsigned short EXT_INIT_MAX_LEN ; 
 unsigned short EXT_UNWRITTEN_MAX_LEN ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 unsigned short ext4_ext_get_actual_len (struct ext4_extent*) ; 
 scalar_t__ ext4_ext_is_unwritten (struct ext4_extent*) ; 
 scalar_t__ ext4_ext_pblock (struct ext4_extent*) ; 
 scalar_t__ ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

int
ext4_can_extents_be_merged(struct inode *inode, struct ext4_extent *ex1,
				struct ext4_extent *ex2)
{
	unsigned short ext1_ee_len, ext2_ee_len;

	if (ext4_ext_is_unwritten(ex1) != ext4_ext_is_unwritten(ex2))
		return 0;

	ext1_ee_len = ext4_ext_get_actual_len(ex1);
	ext2_ee_len = ext4_ext_get_actual_len(ex2);

	if (le32_to_cpu(ex1->ee_block) + ext1_ee_len !=
			le32_to_cpu(ex2->ee_block))
		return 0;

	/*
	 * To allow future support for preallocated extents to be added
	 * as an RO_COMPAT feature, refuse to merge to extents if
	 * this can result in the top bit of ee_len being set.
	 */
	if (ext1_ee_len + ext2_ee_len > EXT_INIT_MAX_LEN)
		return 0;
	/*
	 * The check for IO to unwritten extent is somewhat racy as we
	 * increment i_unwritten / set EXT4_STATE_DIO_UNWRITTEN only after
	 * dropping i_data_sem. But reserved blocks should save us in that
	 * case.
	 */
	if (ext4_ext_is_unwritten(ex1) &&
	    (ext4_test_inode_state(inode, EXT4_STATE_DIO_UNWRITTEN) ||
	     atomic_read(&EXT4_I(inode)->i_unwritten) ||
	     (ext1_ee_len + ext2_ee_len > EXT_UNWRITTEN_MAX_LEN)))
		return 0;
#ifdef AGGRESSIVE_TEST
	if (ext1_ee_len >= 4)
		return 0;
#endif

	if (ext4_ext_pblock(ex1) + ext1_ee_len == ext4_ext_pblock(ex2))
		return 1;
	return 0;
}