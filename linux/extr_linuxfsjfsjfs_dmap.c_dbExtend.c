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
typedef  int uint ;
struct metapage {scalar_t__ data; } ;
struct jfs_sb_info {int nbperpage; struct bmap* bmap; struct inode* ipbmap; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dmap {int dummy; } ;
struct bmap {int db_mapsize; int db_agsize; int /*<<< orphan*/  db_l2nbperpage; } ;
typedef  int s64 ;

/* Variables and functions */
 int BLKTODMAP (int,int /*<<< orphan*/ ) ; 
 int BPERDMAP ; 
 int EIO ; 
 int ENOSPC ; 
 int /*<<< orphan*/  IREAD_LOCK (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IREAD_UNLOCK (struct inode*) ; 
 struct jfs_sb_info* JFS_SBI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSIZE ; 
 int /*<<< orphan*/  RDWRLOCK_DMAP ; 
 int dbAllocNext (struct bmap*,struct dmap*,int,int) ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 
 struct metapage* read_metapage (struct inode*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 
 int /*<<< orphan*/  write_metapage (struct metapage*) ; 

__attribute__((used)) static int dbExtend(struct inode *ip, s64 blkno, s64 nblocks, s64 addnblocks)
{
	struct jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	s64 lblkno, lastblkno, extblkno;
	uint rel_block;
	struct metapage *mp;
	struct dmap *dp;
	int rc;
	struct inode *ipbmap = sbi->ipbmap;
	struct bmap *bmp;

	/*
	 * We don't want a non-aligned extent to cross a page boundary
	 */
	if (((rel_block = blkno & (sbi->nbperpage - 1))) &&
	    (rel_block + nblocks + addnblocks > sbi->nbperpage))
		return -ENOSPC;

	/* get the last block of the current allocation */
	lastblkno = blkno + nblocks - 1;

	/* determine the block number of the block following
	 * the existing allocation.
	 */
	extblkno = lastblkno + 1;

	IREAD_LOCK(ipbmap, RDWRLOCK_DMAP);

	/* better be within the file system */
	bmp = sbi->bmap;
	if (lastblkno < 0 || lastblkno >= bmp->db_mapsize) {
		IREAD_UNLOCK(ipbmap);
		jfs_error(ip->i_sb, "the block is outside the filesystem\n");
		return -EIO;
	}

	/* we'll attempt to extend the current allocation in place by
	 * allocating the additional blocks as the blocks immediately
	 * following the current allocation.  we only try to extend the
	 * current allocation in place if the number of additional blocks
	 * can fit into a dmap, the last block of the current allocation
	 * is not the last block of the file system, and the start of the
	 * inplace extension is not on an allocation group boundary.
	 */
	if (addnblocks > BPERDMAP || extblkno >= bmp->db_mapsize ||
	    (extblkno & (bmp->db_agsize - 1)) == 0) {
		IREAD_UNLOCK(ipbmap);
		return -ENOSPC;
	}

	/* get the buffer for the dmap containing the first block
	 * of the extension.
	 */
	lblkno = BLKTODMAP(extblkno, bmp->db_l2nbperpage);
	mp = read_metapage(ipbmap, lblkno, PSIZE, 0);
	if (mp == NULL) {
		IREAD_UNLOCK(ipbmap);
		return -EIO;
	}

	dp = (struct dmap *) mp->data;

	/* try to allocate the blocks immediately following the
	 * current allocation.
	 */
	rc = dbAllocNext(bmp, dp, extblkno, (int) addnblocks);

	IREAD_UNLOCK(ipbmap);

	/* were we successful ? */
	if (rc == 0)
		write_metapage(mp);
	else
		/* we were not successful */
		release_metapage(mp);

	return (rc);
}