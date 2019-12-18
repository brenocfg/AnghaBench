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
struct inode {unsigned int i_blkbits; } ;
struct ext4_map_blocks {int m_len; int m_flags; scalar_t__ m_lblk; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EXT4_MAP_MAPPED ; 
 int EXT4_MAX_BLOCKS (scalar_t__,scalar_t__,unsigned int) ; 
 int ext4_map_blocks (int /*<<< orphan*/ *,struct inode*,struct ext4_map_blocks*,int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 

__attribute__((used)) static bool ext4_overwrite_io(struct inode *inode, loff_t pos, loff_t len)
{
	struct ext4_map_blocks map;
	unsigned int blkbits = inode->i_blkbits;
	int err, blklen;

	if (pos + len > i_size_read(inode))
		return false;

	map.m_lblk = pos >> blkbits;
	map.m_len = EXT4_MAX_BLOCKS(len, pos, blkbits);
	blklen = map.m_len;

	err = ext4_map_blocks(NULL, inode, &map, 0);
	/*
	 * 'err==len' means that all of the blocks have been preallocated,
	 * regardless of whether they have been initialized or not. To exclude
	 * unwritten extents, we need to check m_flags.
	 */
	return err == blklen && (map.m_flags & EXT4_MAP_MAPPED);
}