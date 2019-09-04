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
typedef  int /*<<< orphan*/  xfs_fileoff_t ;
typedef  int /*<<< orphan*/  xfs_daddr_t ;
typedef  scalar_t__ xfs_dablk_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct xfs_mount {int /*<<< orphan*/  m_ddev_targp; } ;
struct xfs_da_args {int rmtblkcnt; int flags; int rmtvaluelen; int valuelen; int /*<<< orphan*/  trans; TYPE_1__* dp; int /*<<< orphan*/ * value; scalar_t__ rmtblkno; } ;
struct xfs_buf {int dummy; } ;
struct xfs_bmbt_irec {scalar_t__ br_startblock; scalar_t__ br_blockcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_ino; struct xfs_mount* i_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ATTR_KERNOVAL ; 
 int ATTR_RMTVALUE_MAPSIZE ; 
 scalar_t__ DELAYSTARTBLOCK ; 
 scalar_t__ HOLESTARTBLOCK ; 
 int /*<<< orphan*/  XFS_BMAPI_ATTRFORK ; 
 int XFS_FSB_TO_BB (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  XFS_FSB_TO_DADDR (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_attr_rmtval_get (struct xfs_da_args*) ; 
 int /*<<< orphan*/  xfs_attr3_rmt_buf_ops ; 
 int xfs_attr_rmtval_copyout (struct xfs_mount*,struct xfs_buf*,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ **) ; 
 int xfs_bmapi_read (TYPE_1__*,int /*<<< orphan*/ ,int,struct xfs_bmbt_irec*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_brelse (int /*<<< orphan*/ ,struct xfs_buf*) ; 
 int xfs_trans_read_buf (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct xfs_buf**,int /*<<< orphan*/ *) ; 

int
xfs_attr_rmtval_get(
	struct xfs_da_args	*args)
{
	struct xfs_bmbt_irec	map[ATTR_RMTVALUE_MAPSIZE];
	struct xfs_mount	*mp = args->dp->i_mount;
	struct xfs_buf		*bp;
	xfs_dablk_t		lblkno = args->rmtblkno;
	uint8_t			*dst = args->value;
	int			valuelen;
	int			nmap;
	int			error;
	int			blkcnt = args->rmtblkcnt;
	int			i;
	int			offset = 0;

	trace_xfs_attr_rmtval_get(args);

	ASSERT(!(args->flags & ATTR_KERNOVAL));
	ASSERT(args->rmtvaluelen == args->valuelen);

	valuelen = args->rmtvaluelen;
	while (valuelen > 0) {
		nmap = ATTR_RMTVALUE_MAPSIZE;
		error = xfs_bmapi_read(args->dp, (xfs_fileoff_t)lblkno,
				       blkcnt, map, &nmap,
				       XFS_BMAPI_ATTRFORK);
		if (error)
			return error;
		ASSERT(nmap >= 1);

		for (i = 0; (i < nmap) && (valuelen > 0); i++) {
			xfs_daddr_t	dblkno;
			int		dblkcnt;

			ASSERT((map[i].br_startblock != DELAYSTARTBLOCK) &&
			       (map[i].br_startblock != HOLESTARTBLOCK));
			dblkno = XFS_FSB_TO_DADDR(mp, map[i].br_startblock);
			dblkcnt = XFS_FSB_TO_BB(mp, map[i].br_blockcount);
			error = xfs_trans_read_buf(mp, args->trans,
						   mp->m_ddev_targp,
						   dblkno, dblkcnt, 0, &bp,
						   &xfs_attr3_rmt_buf_ops);
			if (error)
				return error;

			error = xfs_attr_rmtval_copyout(mp, bp, args->dp->i_ino,
							&offset, &valuelen,
							&dst);
			xfs_trans_brelse(args->trans, bp);
			if (error)
				return error;

			/* roll attribute extent map forwards */
			lblkno += map[i].br_blockcount;
			blkcnt -= map[i].br_blockcount;
		}
	}
	ASSERT(valuelen == 0);
	return 0;
}