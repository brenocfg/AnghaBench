#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_fsblock_t ;
typedef  int /*<<< orphan*/  xfs_exntst_t ;
struct xfs_trans {int dummy; } ;
struct TYPE_5__ {int rui_nextents; struct xfs_map_extent* rui_extents; } ;
struct xfs_rui_log_item {int /*<<< orphan*/  rui_flags; TYPE_2__ rui_format; } ;
struct xfs_rud_log_item {int dummy; } ;
struct TYPE_4__ {scalar_t__ sb_dblocks; scalar_t__ sb_agblocks; } ;
struct xfs_mount {int /*<<< orphan*/  m_rmap_maxlevels; TYPE_1__ m_sb; } ;
struct xfs_map_extent {int me_flags; scalar_t__ me_len; int /*<<< orphan*/  me_startblock; int /*<<< orphan*/  me_startoff; int /*<<< orphan*/  me_owner; } ;
struct xfs_btree_cur {int dummy; } ;
typedef  enum xfs_rmap_intent_type { ____Placeholder_xfs_rmap_intent_type } xfs_rmap_intent_type ;
struct TYPE_6__ {int /*<<< orphan*/  tr_itruncate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EFSCORRUPTED ; 
 int EIO ; 
 TYPE_3__* M_RES (struct xfs_mount*) ; 
 int XFS_ATTR_FORK ; 
 scalar_t__ XFS_BB_TO_FSB (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int XFS_DATA_FORK ; 
 int /*<<< orphan*/  XFS_EXT_NORM ; 
 int /*<<< orphan*/  XFS_EXT_UNWRITTEN ; 
 int /*<<< orphan*/  XFS_FSB_TO_DADDR (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int XFS_RMAP_ALLOC ; 
 int XFS_RMAP_CONVERT ; 
 int XFS_RMAP_CONVERT_SHARED ; 
#define  XFS_RMAP_EXTENT_ALLOC 135 
 int XFS_RMAP_EXTENT_ATTR_FORK ; 
#define  XFS_RMAP_EXTENT_CONVERT 134 
#define  XFS_RMAP_EXTENT_CONVERT_SHARED 133 
 int XFS_RMAP_EXTENT_FLAGS ; 
#define  XFS_RMAP_EXTENT_FREE 132 
#define  XFS_RMAP_EXTENT_MAP 131 
#define  XFS_RMAP_EXTENT_MAP_SHARED 130 
 int XFS_RMAP_EXTENT_TYPE_MASK ; 
#define  XFS_RMAP_EXTENT_UNMAP 129 
#define  XFS_RMAP_EXTENT_UNMAP_SHARED 128 
 int XFS_RMAP_EXTENT_UNWRITTEN ; 
 int XFS_RMAP_FREE ; 
 int XFS_RMAP_MAP ; 
 int XFS_RMAP_MAP_SHARED ; 
 int XFS_RMAP_UNMAP ; 
 int XFS_RMAP_UNMAP_SHARED ; 
 int /*<<< orphan*/  XFS_RUI_RECOVERED ; 
 int /*<<< orphan*/  XFS_TRANS_RESERVE ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_rmap_finish_one_cleanup (struct xfs_trans*,struct xfs_btree_cur*,int) ; 
 int /*<<< orphan*/  xfs_rui_release (struct xfs_rui_log_item*) ; 
 int xfs_trans_alloc (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_trans**) ; 
 int /*<<< orphan*/  xfs_trans_cancel (struct xfs_trans*) ; 
 int xfs_trans_commit (struct xfs_trans*) ; 
 struct xfs_rud_log_item* xfs_trans_get_rud (struct xfs_trans*,struct xfs_rui_log_item*) ; 
 int xfs_trans_log_finish_rmap_update (struct xfs_trans*,struct xfs_rud_log_item*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct xfs_btree_cur**) ; 

int
xfs_rui_recover(
	struct xfs_mount		*mp,
	struct xfs_rui_log_item		*ruip)
{
	int				i;
	int				error = 0;
	struct xfs_map_extent		*rmap;
	xfs_fsblock_t			startblock_fsb;
	bool				op_ok;
	struct xfs_rud_log_item		*rudp;
	enum xfs_rmap_intent_type	type;
	int				whichfork;
	xfs_exntst_t			state;
	struct xfs_trans		*tp;
	struct xfs_btree_cur		*rcur = NULL;

	ASSERT(!test_bit(XFS_RUI_RECOVERED, &ruip->rui_flags));

	/*
	 * First check the validity of the extents described by the
	 * RUI.  If any are bad, then assume that all are bad and
	 * just toss the RUI.
	 */
	for (i = 0; i < ruip->rui_format.rui_nextents; i++) {
		rmap = &ruip->rui_format.rui_extents[i];
		startblock_fsb = XFS_BB_TO_FSB(mp,
				   XFS_FSB_TO_DADDR(mp, rmap->me_startblock));
		switch (rmap->me_flags & XFS_RMAP_EXTENT_TYPE_MASK) {
		case XFS_RMAP_EXTENT_MAP:
		case XFS_RMAP_EXTENT_MAP_SHARED:
		case XFS_RMAP_EXTENT_UNMAP:
		case XFS_RMAP_EXTENT_UNMAP_SHARED:
		case XFS_RMAP_EXTENT_CONVERT:
		case XFS_RMAP_EXTENT_CONVERT_SHARED:
		case XFS_RMAP_EXTENT_ALLOC:
		case XFS_RMAP_EXTENT_FREE:
			op_ok = true;
			break;
		default:
			op_ok = false;
			break;
		}
		if (!op_ok || startblock_fsb == 0 ||
		    rmap->me_len == 0 ||
		    startblock_fsb >= mp->m_sb.sb_dblocks ||
		    rmap->me_len >= mp->m_sb.sb_agblocks ||
		    (rmap->me_flags & ~XFS_RMAP_EXTENT_FLAGS)) {
			/*
			 * This will pull the RUI from the AIL and
			 * free the memory associated with it.
			 */
			set_bit(XFS_RUI_RECOVERED, &ruip->rui_flags);
			xfs_rui_release(ruip);
			return -EIO;
		}
	}

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_itruncate,
			mp->m_rmap_maxlevels, 0, XFS_TRANS_RESERVE, &tp);
	if (error)
		return error;
	rudp = xfs_trans_get_rud(tp, ruip);

	for (i = 0; i < ruip->rui_format.rui_nextents; i++) {
		rmap = &ruip->rui_format.rui_extents[i];
		state = (rmap->me_flags & XFS_RMAP_EXTENT_UNWRITTEN) ?
				XFS_EXT_UNWRITTEN : XFS_EXT_NORM;
		whichfork = (rmap->me_flags & XFS_RMAP_EXTENT_ATTR_FORK) ?
				XFS_ATTR_FORK : XFS_DATA_FORK;
		switch (rmap->me_flags & XFS_RMAP_EXTENT_TYPE_MASK) {
		case XFS_RMAP_EXTENT_MAP:
			type = XFS_RMAP_MAP;
			break;
		case XFS_RMAP_EXTENT_MAP_SHARED:
			type = XFS_RMAP_MAP_SHARED;
			break;
		case XFS_RMAP_EXTENT_UNMAP:
			type = XFS_RMAP_UNMAP;
			break;
		case XFS_RMAP_EXTENT_UNMAP_SHARED:
			type = XFS_RMAP_UNMAP_SHARED;
			break;
		case XFS_RMAP_EXTENT_CONVERT:
			type = XFS_RMAP_CONVERT;
			break;
		case XFS_RMAP_EXTENT_CONVERT_SHARED:
			type = XFS_RMAP_CONVERT_SHARED;
			break;
		case XFS_RMAP_EXTENT_ALLOC:
			type = XFS_RMAP_ALLOC;
			break;
		case XFS_RMAP_EXTENT_FREE:
			type = XFS_RMAP_FREE;
			break;
		default:
			error = -EFSCORRUPTED;
			goto abort_error;
		}
		error = xfs_trans_log_finish_rmap_update(tp, rudp, type,
				rmap->me_owner, whichfork,
				rmap->me_startoff, rmap->me_startblock,
				rmap->me_len, state, &rcur);
		if (error)
			goto abort_error;

	}

	xfs_rmap_finish_one_cleanup(tp, rcur, error);
	set_bit(XFS_RUI_RECOVERED, &ruip->rui_flags);
	error = xfs_trans_commit(tp);
	return error;

abort_error:
	xfs_rmap_finish_one_cleanup(tp, rcur, error);
	xfs_trans_cancel(tp);
	return error;
}