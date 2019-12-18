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
typedef  scalar_t__ xfs_fileoff_t ;
typedef  int /*<<< orphan*/  xfs_daddr_t ;
typedef  scalar_t__ xfs_dablk_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct xfs_mount {int /*<<< orphan*/  m_ddev_targp; } ;
struct xfs_inode {int /*<<< orphan*/  i_ino; struct xfs_mount* i_mount; } ;
struct xfs_da_args {int rmtvaluelen; int rmtblkcnt; struct xfs_inode* dp; scalar_t__ rmtblkno; int /*<<< orphan*/  trans; int /*<<< orphan*/  total; int /*<<< orphan*/ * value; } ;
struct xfs_buf {int /*<<< orphan*/ * b_ops; } ;
struct xfs_bmbt_irec {scalar_t__ br_startblock; scalar_t__ br_blockcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DELAYSTARTBLOCK ; 
 int ENOMEM ; 
 scalar_t__ HOLESTARTBLOCK ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_BMAPI_ATTRFORK ; 
 int XFS_FSB_TO_BB (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  XFS_FSB_TO_DADDR (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_attr_rmtval_set (struct xfs_da_args*) ; 
 int xfs_attr3_rmt_blocks (struct xfs_mount*,int) ; 
 int /*<<< orphan*/  xfs_attr3_rmt_buf_ops ; 
 int /*<<< orphan*/  xfs_attr_rmtval_copyin (struct xfs_mount*,struct xfs_buf*,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ **) ; 
 int xfs_bmap_first_unused (int /*<<< orphan*/ ,struct xfs_inode*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int xfs_bmapi_read (struct xfs_inode*,scalar_t__,int,struct xfs_bmbt_irec*,int*,int /*<<< orphan*/ ) ; 
 int xfs_bmapi_write (int /*<<< orphan*/ ,struct xfs_inode*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_bmbt_irec*,int*) ; 
 struct xfs_buf* xfs_buf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_buf_relse (struct xfs_buf*) ; 
 int xfs_bwrite (struct xfs_buf*) ; 
 int xfs_defer_finish (int /*<<< orphan*/ *) ; 
 int xfs_trans_roll_inode (int /*<<< orphan*/ *,struct xfs_inode*) ; 

int
xfs_attr_rmtval_set(
	struct xfs_da_args	*args)
{
	struct xfs_inode	*dp = args->dp;
	struct xfs_mount	*mp = dp->i_mount;
	struct xfs_bmbt_irec	map;
	xfs_dablk_t		lblkno;
	xfs_fileoff_t		lfileoff = 0;
	uint8_t			*src = args->value;
	int			blkcnt;
	int			valuelen;
	int			nmap;
	int			error;
	int			offset = 0;

	trace_xfs_attr_rmtval_set(args);

	/*
	 * Find a "hole" in the attribute address space large enough for
	 * us to drop the new attribute's value into. Because CRC enable
	 * attributes have headers, we can't just do a straight byte to FSB
	 * conversion and have to take the header space into account.
	 */
	blkcnt = xfs_attr3_rmt_blocks(mp, args->rmtvaluelen);
	error = xfs_bmap_first_unused(args->trans, args->dp, blkcnt, &lfileoff,
						   XFS_ATTR_FORK);
	if (error)
		return error;

	args->rmtblkno = lblkno = (xfs_dablk_t)lfileoff;
	args->rmtblkcnt = blkcnt;

	/*
	 * Roll through the "value", allocating blocks on disk as required.
	 */
	while (blkcnt > 0) {
		/*
		 * Allocate a single extent, up to the size of the value.
		 *
		 * Note that we have to consider this a data allocation as we
		 * write the remote attribute without logging the contents.
		 * Hence we must ensure that we aren't using blocks that are on
		 * the busy list so that we don't overwrite blocks which have
		 * recently been freed but their transactions are not yet
		 * committed to disk. If we overwrite the contents of a busy
		 * extent and then crash then the block may not contain the
		 * correct metadata after log recovery occurs.
		 */
		nmap = 1;
		error = xfs_bmapi_write(args->trans, dp, (xfs_fileoff_t)lblkno,
				  blkcnt, XFS_BMAPI_ATTRFORK, args->total, &map,
				  &nmap);
		if (error)
			return error;
		error = xfs_defer_finish(&args->trans);
		if (error)
			return error;

		ASSERT(nmap == 1);
		ASSERT((map.br_startblock != DELAYSTARTBLOCK) &&
		       (map.br_startblock != HOLESTARTBLOCK));
		lblkno += map.br_blockcount;
		blkcnt -= map.br_blockcount;

		/*
		 * Start the next trans in the chain.
		 */
		error = xfs_trans_roll_inode(&args->trans, dp);
		if (error)
			return error;
	}

	/*
	 * Roll through the "value", copying the attribute value to the
	 * already-allocated blocks.  Blocks are written synchronously
	 * so that we can know they are all on disk before we turn off
	 * the INCOMPLETE flag.
	 */
	lblkno = args->rmtblkno;
	blkcnt = args->rmtblkcnt;
	valuelen = args->rmtvaluelen;
	while (valuelen > 0) {
		struct xfs_buf	*bp;
		xfs_daddr_t	dblkno;
		int		dblkcnt;

		ASSERT(blkcnt > 0);

		nmap = 1;
		error = xfs_bmapi_read(dp, (xfs_fileoff_t)lblkno,
				       blkcnt, &map, &nmap,
				       XFS_BMAPI_ATTRFORK);
		if (error)
			return error;
		ASSERT(nmap == 1);
		ASSERT((map.br_startblock != DELAYSTARTBLOCK) &&
		       (map.br_startblock != HOLESTARTBLOCK));

		dblkno = XFS_FSB_TO_DADDR(mp, map.br_startblock),
		dblkcnt = XFS_FSB_TO_BB(mp, map.br_blockcount);

		bp = xfs_buf_get(mp->m_ddev_targp, dblkno, dblkcnt);
		if (!bp)
			return -ENOMEM;
		bp->b_ops = &xfs_attr3_rmt_buf_ops;

		xfs_attr_rmtval_copyin(mp, bp, args->dp->i_ino, &offset,
				       &valuelen, &src);

		error = xfs_bwrite(bp);	/* GROT: NOTE: synchronous write */
		xfs_buf_relse(bp);
		if (error)
			return error;


		/* roll attribute extent map forwards */
		lblkno += map.br_blockcount;
		blkcnt -= map.br_blockcount;
	}
	ASSERT(valuelen == 0);
	return 0;
}