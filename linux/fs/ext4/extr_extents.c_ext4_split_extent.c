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
struct ext4_map_blocks {int m_len; scalar_t__ m_lblk; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
struct ext4_ext_path {struct ext4_extent* p_ext; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ ext4_lblk_t ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*,unsigned long) ; 
 int EXT4_EXT_DATA_VALID1 ; 
 int EXT4_EXT_DATA_VALID2 ; 
 int EXT4_EXT_MARK_UNWRIT1 ; 
 int EXT4_EXT_MARK_UNWRIT2 ; 
 int EXT4_EXT_MAY_ZEROOUT ; 
 int EXT4_GET_BLOCKS_PRE_IO ; 
 scalar_t__ IS_ERR (struct ext4_ext_path*) ; 
 int PTR_ERR (struct ext4_ext_path*) ; 
 unsigned int ext4_ext_get_actual_len (struct ext4_extent*) ; 
 int ext4_ext_is_unwritten (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_show_leaf (struct inode*,struct ext4_ext_path*) ; 
 struct ext4_ext_path* ext4_find_extent (struct inode*,scalar_t__,struct ext4_ext_path**,int /*<<< orphan*/ ) ; 
 int ext4_split_extent_at (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path**,scalar_t__,int,int) ; 
 unsigned int ext_depth (struct inode*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_split_extent(handle_t *handle,
			      struct inode *inode,
			      struct ext4_ext_path **ppath,
			      struct ext4_map_blocks *map,
			      int split_flag,
			      int flags)
{
	struct ext4_ext_path *path = *ppath;
	ext4_lblk_t ee_block;
	struct ext4_extent *ex;
	unsigned int ee_len, depth;
	int err = 0;
	int unwritten;
	int split_flag1, flags1;
	int allocated = map->m_len;

	depth = ext_depth(inode);
	ex = path[depth].p_ext;
	ee_block = le32_to_cpu(ex->ee_block);
	ee_len = ext4_ext_get_actual_len(ex);
	unwritten = ext4_ext_is_unwritten(ex);

	if (map->m_lblk + map->m_len < ee_block + ee_len) {
		split_flag1 = split_flag & EXT4_EXT_MAY_ZEROOUT;
		flags1 = flags | EXT4_GET_BLOCKS_PRE_IO;
		if (unwritten)
			split_flag1 |= EXT4_EXT_MARK_UNWRIT1 |
				       EXT4_EXT_MARK_UNWRIT2;
		if (split_flag & EXT4_EXT_DATA_VALID2)
			split_flag1 |= EXT4_EXT_DATA_VALID1;
		err = ext4_split_extent_at(handle, inode, ppath,
				map->m_lblk + map->m_len, split_flag1, flags1);
		if (err)
			goto out;
	} else {
		allocated = ee_len - (map->m_lblk - ee_block);
	}
	/*
	 * Update path is required because previous ext4_split_extent_at() may
	 * result in split of original leaf or extent zeroout.
	 */
	path = ext4_find_extent(inode, map->m_lblk, ppath, 0);
	if (IS_ERR(path))
		return PTR_ERR(path);
	depth = ext_depth(inode);
	ex = path[depth].p_ext;
	if (!ex) {
		EXT4_ERROR_INODE(inode, "unexpected hole at %lu",
				 (unsigned long) map->m_lblk);
		return -EFSCORRUPTED;
	}
	unwritten = ext4_ext_is_unwritten(ex);
	split_flag1 = 0;

	if (map->m_lblk >= ee_block) {
		split_flag1 = split_flag & EXT4_EXT_DATA_VALID2;
		if (unwritten) {
			split_flag1 |= EXT4_EXT_MARK_UNWRIT1;
			split_flag1 |= split_flag & (EXT4_EXT_MAY_ZEROOUT |
						     EXT4_EXT_MARK_UNWRIT2);
		}
		err = ext4_split_extent_at(handle, inode, ppath,
				map->m_lblk, split_flag1, flags);
		if (err)
			goto out;
	}

	ext4_ext_show_leaf(inode, path);
out:
	return err ? err : allocated;
}