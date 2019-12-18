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
struct f2fs_map_blocks {scalar_t__ m_lblk; int m_may_create; scalar_t__ m_len; int /*<<< orphan*/  m_seg_type; int /*<<< orphan*/ * m_next_extent; int /*<<< orphan*/ * m_next_pgofs; } ;
typedef  scalar_t__ loff_t ;
typedef  scalar_t__ block_t ;

/* Variables and functions */
 scalar_t__ F2FS_BLK_ALIGN (scalar_t__) ; 
 scalar_t__ F2FS_BYTES_TO_BLK (scalar_t__) ; 
 int /*<<< orphan*/  F2FS_GET_BLOCK_DEFAULT ; 
 int /*<<< orphan*/  NO_CHECK_TYPE ; 
 int f2fs_map_blocks (struct inode*,struct f2fs_map_blocks*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 

bool f2fs_overwrite_io(struct inode *inode, loff_t pos, size_t len)
{
	struct f2fs_map_blocks map;
	block_t last_lblk;
	int err;

	if (pos + len > i_size_read(inode))
		return false;

	map.m_lblk = F2FS_BYTES_TO_BLK(pos);
	map.m_next_pgofs = NULL;
	map.m_next_extent = NULL;
	map.m_seg_type = NO_CHECK_TYPE;
	map.m_may_create = false;
	last_lblk = F2FS_BLK_ALIGN(pos + len);

	while (map.m_lblk < last_lblk) {
		map.m_len = last_lblk - map.m_lblk;
		err = f2fs_map_blocks(inode, &map, 0, F2FS_GET_BLOCK_DEFAULT);
		if (err || map.m_len == 0)
			return false;
		map.m_lblk += map.m_len;
	}
	return true;
}