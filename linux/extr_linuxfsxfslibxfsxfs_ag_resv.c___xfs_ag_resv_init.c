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
typedef  scalar_t__ xfs_extlen_t ;
struct xfs_perag {int /*<<< orphan*/  pag_agno; struct xfs_mount* pag_mount; } ;
struct xfs_mount {int /*<<< orphan*/  m_ag_max_usable; } ;
struct xfs_ag_resv {scalar_t__ ar_reserved; scalar_t__ ar_orig_reserved; scalar_t__ ar_asked; } ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  enum xfs_ag_resv_type { ____Placeholder_xfs_ag_resv_type } xfs_ag_resv_type ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  XFS_AG_RESV_METADATA 129 
#define  XFS_AG_RESV_RMAPBT 128 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  trace_xfs_ag_resv_init (struct xfs_perag*,int,scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_ag_resv_init_error (struct xfs_mount*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int xfs_mod_fdblocks (struct xfs_mount*,int /*<<< orphan*/ ,int) ; 
 struct xfs_ag_resv* xfs_perag_resv (struct xfs_perag*,int) ; 
 int /*<<< orphan*/  xfs_warn (struct xfs_mount*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__xfs_ag_resv_init(
	struct xfs_perag		*pag,
	enum xfs_ag_resv_type		type,
	xfs_extlen_t			ask,
	xfs_extlen_t			used)
{
	struct xfs_mount		*mp = pag->pag_mount;
	struct xfs_ag_resv		*resv;
	int				error;
	xfs_extlen_t			hidden_space;

	if (used > ask)
		ask = used;

	switch (type) {
	case XFS_AG_RESV_RMAPBT:
		/*
		 * Space taken by the rmapbt is not subtracted from fdblocks
		 * because the rmapbt lives in the free space.  Here we must
		 * subtract the entire reservation from fdblocks so that we
		 * always have blocks available for rmapbt expansion.
		 */
		hidden_space = ask;
		break;
	case XFS_AG_RESV_METADATA:
		/*
		 * Space taken by all other metadata btrees are accounted
		 * on-disk as used space.  We therefore only hide the space
		 * that is reserved but not used by the trees.
		 */
		hidden_space = ask - used;
		break;
	default:
		ASSERT(0);
		return -EINVAL;
	}
	error = xfs_mod_fdblocks(mp, -(int64_t)hidden_space, true);
	if (error) {
		trace_xfs_ag_resv_init_error(pag->pag_mount, pag->pag_agno,
				error, _RET_IP_);
		xfs_warn(mp,
"Per-AG reservation for AG %u failed.  Filesystem may run out of space.",
				pag->pag_agno);
		return error;
	}

	/*
	 * Reduce the maximum per-AG allocation length by however much we're
	 * trying to reserve for an AG.  Since this is a filesystem-wide
	 * counter, we only make the adjustment for AG 0.  This assumes that
	 * there aren't any AGs hungrier for per-AG reservation than AG 0.
	 */
	if (pag->pag_agno == 0)
		mp->m_ag_max_usable -= ask;

	resv = xfs_perag_resv(pag, type);
	resv->ar_asked = ask;
	resv->ar_orig_reserved = hidden_space;
	resv->ar_reserved = ask - used;

	trace_xfs_ag_resv_init(pag, type, ask);
	return 0;
}