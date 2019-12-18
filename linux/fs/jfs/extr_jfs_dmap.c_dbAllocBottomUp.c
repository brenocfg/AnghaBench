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
struct metapage {scalar_t__ data; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dmap {int dummy; } ;
struct bmap {scalar_t__ db_mapsize; int /*<<< orphan*/  db_l2nbperpage; } ;
typedef  scalar_t__ s64 ;
struct TYPE_2__ {struct bmap* bmap; struct inode* ipbmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BLKTODMAP (scalar_t__,int /*<<< orphan*/ ) ; 
 int BPERDMAP ; 
 int EIO ; 
 int /*<<< orphan*/  IREAD_LOCK (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IREAD_UNLOCK (struct inode*) ; 
 TYPE_1__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSIZE ; 
 int /*<<< orphan*/  RDWRLOCK_DMAP ; 
 int dbAllocDmapBU (struct bmap*,struct dmap*,scalar_t__,int) ; 
 int min (scalar_t__,int) ; 
 struct metapage* read_metapage (struct inode*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 
 int /*<<< orphan*/  write_metapage (struct metapage*) ; 

int dbAllocBottomUp(struct inode *ip, s64 blkno, s64 nblocks)
{
	struct metapage *mp;
	struct dmap *dp;
	int nb, rc;
	s64 lblkno, rem;
	struct inode *ipbmap = JFS_SBI(ip->i_sb)->ipbmap;
	struct bmap *bmp = JFS_SBI(ip->i_sb)->bmap;

	IREAD_LOCK(ipbmap, RDWRLOCK_DMAP);

	/* block to be allocated better be within the mapsize. */
	ASSERT(nblocks <= bmp->db_mapsize - blkno);

	/*
	 * allocate the blocks a dmap at a time.
	 */
	mp = NULL;
	for (rem = nblocks; rem > 0; rem -= nb, blkno += nb) {
		/* release previous dmap if any */
		if (mp) {
			write_metapage(mp);
		}

		/* get the buffer for the current dmap. */
		lblkno = BLKTODMAP(blkno, bmp->db_l2nbperpage);
		mp = read_metapage(ipbmap, lblkno, PSIZE, 0);
		if (mp == NULL) {
			IREAD_UNLOCK(ipbmap);
			return -EIO;
		}
		dp = (struct dmap *) mp->data;

		/* determine the number of blocks to be allocated from
		 * this dmap.
		 */
		nb = min(rem, BPERDMAP - (blkno & (BPERDMAP - 1)));

		/* allocate the blocks. */
		if ((rc = dbAllocDmapBU(bmp, dp, blkno, nb))) {
			release_metapage(mp);
			IREAD_UNLOCK(ipbmap);
			return (rc);
		}
	}

	/* write the last buffer. */
	write_metapage(mp);

	IREAD_UNLOCK(ipbmap);

	return (0);
}