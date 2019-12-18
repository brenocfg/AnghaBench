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
typedef  scalar_t__ xfs_agnumber_t ;
struct xfs_trans {int dummy; } ;
struct xfs_perag {int pagf_init; scalar_t__ pagf_freeblks; scalar_t__ pagf_btreeblks; scalar_t__ pagf_flcount; scalar_t__ pagf_longest; scalar_t__* pagf_levels; int /*<<< orphan*/  pagf_agflreset; scalar_t__ pagf_refcount_level; } ;
struct xfs_mount {int dummy; } ;
struct xfs_buf {int /*<<< orphan*/  b_error; } ;
struct xfs_agf {int /*<<< orphan*/ * agf_levels; int /*<<< orphan*/  agf_longest; int /*<<< orphan*/  agf_flcount; int /*<<< orphan*/  agf_btreeblks; int /*<<< orphan*/  agf_freeblks; int /*<<< orphan*/  agf_refcount_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ NULLAGNUMBER ; 
 int /*<<< orphan*/  XBF_TRYLOCK ; 
 int XFS_ALLOC_FLAG_TRYLOCK ; 
 size_t XFS_BTNUM_BNOi ; 
 size_t XFS_BTNUM_CNTi ; 
 size_t XFS_BTNUM_RMAPi ; 
 struct xfs_agf* XFS_BUF_TO_AGF (struct xfs_buf*) ; 
 int /*<<< orphan*/  XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_alloc_read_agf (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_agfl_needs_reset (struct xfs_mount*,struct xfs_agf*) ; 
 struct xfs_perag* xfs_perag_get (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_perag_put (struct xfs_perag*) ; 
 int xfs_read_agf (struct xfs_mount*,struct xfs_trans*,scalar_t__,int /*<<< orphan*/ ,struct xfs_buf**) ; 

int					/* error */
xfs_alloc_read_agf(
	struct xfs_mount	*mp,	/* mount point structure */
	struct xfs_trans	*tp,	/* transaction pointer */
	xfs_agnumber_t		agno,	/* allocation group number */
	int			flags,	/* XFS_ALLOC_FLAG_... */
	struct xfs_buf		**bpp)	/* buffer for the ag freelist header */
{
	struct xfs_agf		*agf;		/* ag freelist header */
	struct xfs_perag	*pag;		/* per allocation group data */
	int			error;

	trace_xfs_alloc_read_agf(mp, agno);

	ASSERT(agno != NULLAGNUMBER);
	error = xfs_read_agf(mp, tp, agno,
			(flags & XFS_ALLOC_FLAG_TRYLOCK) ? XBF_TRYLOCK : 0,
			bpp);
	if (error)
		return error;
	if (!*bpp)
		return 0;
	ASSERT(!(*bpp)->b_error);

	agf = XFS_BUF_TO_AGF(*bpp);
	pag = xfs_perag_get(mp, agno);
	if (!pag->pagf_init) {
		pag->pagf_freeblks = be32_to_cpu(agf->agf_freeblks);
		pag->pagf_btreeblks = be32_to_cpu(agf->agf_btreeblks);
		pag->pagf_flcount = be32_to_cpu(agf->agf_flcount);
		pag->pagf_longest = be32_to_cpu(agf->agf_longest);
		pag->pagf_levels[XFS_BTNUM_BNOi] =
			be32_to_cpu(agf->agf_levels[XFS_BTNUM_BNOi]);
		pag->pagf_levels[XFS_BTNUM_CNTi] =
			be32_to_cpu(agf->agf_levels[XFS_BTNUM_CNTi]);
		pag->pagf_levels[XFS_BTNUM_RMAPi] =
			be32_to_cpu(agf->agf_levels[XFS_BTNUM_RMAPi]);
		pag->pagf_refcount_level = be32_to_cpu(agf->agf_refcount_level);
		pag->pagf_init = 1;
		pag->pagf_agflreset = xfs_agfl_needs_reset(mp, agf);
	}
#ifdef DEBUG
	else if (!XFS_FORCED_SHUTDOWN(mp)) {
		ASSERT(pag->pagf_freeblks == be32_to_cpu(agf->agf_freeblks));
		ASSERT(pag->pagf_btreeblks == be32_to_cpu(agf->agf_btreeblks));
		ASSERT(pag->pagf_flcount == be32_to_cpu(agf->agf_flcount));
		ASSERT(pag->pagf_longest == be32_to_cpu(agf->agf_longest));
		ASSERT(pag->pagf_levels[XFS_BTNUM_BNOi] ==
		       be32_to_cpu(agf->agf_levels[XFS_BTNUM_BNOi]));
		ASSERT(pag->pagf_levels[XFS_BTNUM_CNTi] ==
		       be32_to_cpu(agf->agf_levels[XFS_BTNUM_CNTi]));
	}
#endif
	xfs_perag_put(pag);
	return 0;
}