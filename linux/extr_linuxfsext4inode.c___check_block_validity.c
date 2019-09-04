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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_map_blocks {int /*<<< orphan*/  m_len; int /*<<< orphan*/  m_pblk; scalar_t__ m_lblk; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_data_block_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_error_inode (struct inode*,char const*,unsigned int,int /*<<< orphan*/ ,char*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __check_block_validity(struct inode *inode, const char *func,
				unsigned int line,
				struct ext4_map_blocks *map)
{
	if (!ext4_data_block_valid(EXT4_SB(inode->i_sb), map->m_pblk,
				   map->m_len)) {
		ext4_error_inode(inode, func, line, map->m_pblk,
				 "lblock %lu mapped to illegal pblock %llu "
				 "(length %d)", (unsigned long) map->m_lblk,
				 map->m_pblk, map->m_len);
		return -EFSCORRUPTED;
	}
	return 0;
}