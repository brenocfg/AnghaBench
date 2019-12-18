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
struct inode {int dummy; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;

/* Variables and functions */
 unsigned short EXT_INIT_MAX_LEN ; 
 unsigned short EXT_UNWRITTEN_MAX_LEN ; 
 unsigned short ext4_ext_get_actual_len (struct ext4_extent*) ; 
 scalar_t__ ext4_ext_is_unwritten (struct ext4_extent*) ; 
 scalar_t__ ext4_ext_pblock (struct ext4_extent*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

int
ext4_can_extents_be_merged(struct inode *inode, struct ext4_extent *ex1,
		struct ext4_extent *ex2)
{
	unsigned short ext1_ee_len, ext2_ee_len;

	/*
	 * Make sure that both extents are initialized. We don't merge
	 * unwritten extents so that we can be sure that end_io code has
	 * the extent that was written properly split out and conversion to
	 * initialized is trivial.
	 */
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
	if (ext4_ext_is_unwritten(ex1) &&
			(ext1_ee_len + ext2_ee_len > EXT_UNWRITTEN_MAX_LEN))
		return 0;
#ifdef AGGRESSIVE_TEST
	if (ext1_ee_len >= 4)
		return 0;
#endif

	if (ext4_ext_pblock(ex1) + ext1_ee_len == ext4_ext_pblock(ex2))
		return 1;
	return 0;
}