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
typedef  int /*<<< orphan*/  ext4_lblk_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_STATUS_WRITTEN ; 
 int ext4_es_insert_extent (struct inode*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ext4_ext_get_actual_len (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_pblock (struct ext4_extent*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_zeroout_es(struct inode *inode, struct ext4_extent *ex)
{
	ext4_lblk_t  ee_block;
	ext4_fsblk_t ee_pblock;
	unsigned int ee_len;

	ee_block  = le32_to_cpu(ex->ee_block);
	ee_len    = ext4_ext_get_actual_len(ex);
	ee_pblock = ext4_ext_pblock(ex);

	if (ee_len == 0)
		return 0;

	return ext4_es_insert_extent(inode, ee_block, ee_len, ee_pblock,
				     EXTENT_STATUS_WRITTEN);
}