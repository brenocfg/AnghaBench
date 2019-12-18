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
typedef  scalar_t__ xfs_rfsblock_t ;
typedef  scalar_t__ xfs_fileoff_t ;
struct xfs_trans {int dummy; } ;
struct TYPE_2__ {scalar_t__ di_nblocks; } ;
struct xfs_inode {TYPE_1__ i_d; } ;
struct xfs_da_args {int whichfork; int /*<<< orphan*/  total; struct xfs_inode* dp; struct xfs_trans* trans; } ;
struct xfs_bmbt_irec {scalar_t__ br_startoff; scalar_t__ br_blockcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOSPC ; 
 int XFS_BMAPI_CONTIG ; 
 int XFS_BMAPI_METADATA ; 
 int /*<<< orphan*/  XFS_BMAP_MAX_NMAP ; 
 struct xfs_bmbt_irec* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (struct xfs_bmbt_irec*) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int xfs_bmap_first_unused (struct xfs_trans*,struct xfs_inode*,int,scalar_t__*,int) ; 
 int xfs_bmapi_aflag (int) ; 
 int xfs_bmapi_write (struct xfs_trans*,struct xfs_inode*,scalar_t__,int,int,int /*<<< orphan*/ ,struct xfs_bmbt_irec*,int*) ; 

int
xfs_da_grow_inode_int(
	struct xfs_da_args	*args,
	xfs_fileoff_t		*bno,
	int			count)
{
	struct xfs_trans	*tp = args->trans;
	struct xfs_inode	*dp = args->dp;
	int			w = args->whichfork;
	xfs_rfsblock_t		nblks = dp->i_d.di_nblocks;
	struct xfs_bmbt_irec	map, *mapp;
	int			nmap, error, got, i, mapi;

	/*
	 * Find a spot in the file space to put the new block.
	 */
	error = xfs_bmap_first_unused(tp, dp, count, bno, w);
	if (error)
		return error;

	/*
	 * Try mapping it in one filesystem block.
	 */
	nmap = 1;
	error = xfs_bmapi_write(tp, dp, *bno, count,
			xfs_bmapi_aflag(w)|XFS_BMAPI_METADATA|XFS_BMAPI_CONTIG,
			args->total, &map, &nmap);
	if (error)
		return error;

	ASSERT(nmap <= 1);
	if (nmap == 1) {
		mapp = &map;
		mapi = 1;
	} else if (nmap == 0 && count > 1) {
		xfs_fileoff_t		b;
		int			c;

		/*
		 * If we didn't get it and the block might work if fragmented,
		 * try without the CONTIG flag.  Loop until we get it all.
		 */
		mapp = kmem_alloc(sizeof(*mapp) * count, 0);
		for (b = *bno, mapi = 0; b < *bno + count; ) {
			nmap = min(XFS_BMAP_MAX_NMAP, count);
			c = (int)(*bno + count - b);
			error = xfs_bmapi_write(tp, dp, b, c,
					xfs_bmapi_aflag(w)|XFS_BMAPI_METADATA,
					args->total, &mapp[mapi], &nmap);
			if (error)
				goto out_free_map;
			if (nmap < 1)
				break;
			mapi += nmap;
			b = mapp[mapi - 1].br_startoff +
			    mapp[mapi - 1].br_blockcount;
		}
	} else {
		mapi = 0;
		mapp = NULL;
	}

	/*
	 * Count the blocks we got, make sure it matches the total.
	 */
	for (i = 0, got = 0; i < mapi; i++)
		got += mapp[i].br_blockcount;
	if (got != count || mapp[0].br_startoff != *bno ||
	    mapp[mapi - 1].br_startoff + mapp[mapi - 1].br_blockcount !=
	    *bno + count) {
		error = -ENOSPC;
		goto out_free_map;
	}

	/* account for newly allocated blocks in reserved blocks total */
	args->total -= dp->i_d.di_nblocks - nblks;

out_free_map:
	if (mapp != &map)
		kmem_free(mapp);
	return error;
}