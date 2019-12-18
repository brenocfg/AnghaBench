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
typedef  scalar_t__ u64 ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_sb; } ;
struct erofs_sb_info {int dummy; } ;
struct erofs_map_blocks {scalar_t__ m_la; scalar_t__ m_plen; scalar_t__ m_pa; scalar_t__ m_llen; int /*<<< orphan*/  m_flags; } ;
struct erofs_inode {scalar_t__ datalayout; scalar_t__ inode_isize; scalar_t__ xattr_isize; int /*<<< orphan*/  nid; scalar_t__ raw_blkaddr; } ;
typedef  scalar_t__ erofs_blk_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 scalar_t__ DIV_ROUND_UP (scalar_t__,scalar_t__) ; 
 int EFSCORRUPTED ; 
 int EIO ; 
 struct erofs_inode* EROFS_I (struct inode*) ; 
 scalar_t__ EROFS_INODE_FLAT_INLINE ; 
 int /*<<< orphan*/  EROFS_MAP_MAPPED ; 
 int /*<<< orphan*/  EROFS_MAP_META ; 
 struct erofs_sb_info* EROFS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ blknr_to_addr (scalar_t__) ; 
 scalar_t__ erofs_blkoff (scalar_t__) ; 
 int /*<<< orphan*/  erofs_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ iloc (struct erofs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_erofs_map_blocks_flatmode_enter (struct inode*,struct erofs_map_blocks*,int) ; 
 int /*<<< orphan*/  trace_erofs_map_blocks_flatmode_exit (struct inode*,struct erofs_map_blocks*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int erofs_map_blocks_flatmode(struct inode *inode,
				     struct erofs_map_blocks *map,
				     int flags)
{
	int err = 0;
	erofs_blk_t nblocks, lastblk;
	u64 offset = map->m_la;
	struct erofs_inode *vi = EROFS_I(inode);
	bool tailendpacking = (vi->datalayout == EROFS_INODE_FLAT_INLINE);

	trace_erofs_map_blocks_flatmode_enter(inode, map, flags);

	nblocks = DIV_ROUND_UP(inode->i_size, PAGE_SIZE);
	lastblk = nblocks - tailendpacking;

	if (offset >= inode->i_size) {
		/* leave out-of-bound access unmapped */
		map->m_flags = 0;
		map->m_plen = 0;
		goto out;
	}

	/* there is no hole in flatmode */
	map->m_flags = EROFS_MAP_MAPPED;

	if (offset < blknr_to_addr(lastblk)) {
		map->m_pa = blknr_to_addr(vi->raw_blkaddr) + map->m_la;
		map->m_plen = blknr_to_addr(lastblk) - offset;
	} else if (tailendpacking) {
		/* 2 - inode inline B: inode, [xattrs], inline last blk... */
		struct erofs_sb_info *sbi = EROFS_SB(inode->i_sb);

		map->m_pa = iloc(sbi, vi->nid) + vi->inode_isize +
			vi->xattr_isize + erofs_blkoff(map->m_la);
		map->m_plen = inode->i_size - offset;

		/* inline data should be located in one meta block */
		if (erofs_blkoff(map->m_pa) + map->m_plen > PAGE_SIZE) {
			erofs_err(inode->i_sb,
				  "inline data cross block boundary @ nid %llu",
				  vi->nid);
			DBG_BUGON(1);
			err = -EFSCORRUPTED;
			goto err_out;
		}

		map->m_flags |= EROFS_MAP_META;
	} else {
		erofs_err(inode->i_sb,
			  "internal error @ nid: %llu (size %llu), m_la 0x%llx",
			  vi->nid, inode->i_size, map->m_la);
		DBG_BUGON(1);
		err = -EIO;
		goto err_out;
	}

out:
	map->m_llen = map->m_plen;

err_out:
	trace_erofs_map_blocks_flatmode_exit(inode, map, flags, 0);
	return err;
}