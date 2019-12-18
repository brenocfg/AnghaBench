#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_fsblock_t ;
typedef  scalar_t__ xfs_filblks_t ;
typedef  int /*<<< orphan*/  xfs_exntst_t ;
struct xfs_trans {struct xfs_mount* t_mountp; } ;
struct TYPE_6__ {scalar_t__ sb_dblocks; scalar_t__ sb_agblocks; } ;
struct xfs_mount {TYPE_2__ m_sb; } ;
struct xfs_map_extent {int me_flags; scalar_t__ me_len; int /*<<< orphan*/  me_startoff; int /*<<< orphan*/  me_startblock; int /*<<< orphan*/  me_owner; } ;
struct xfs_inode {int dummy; } ;
struct TYPE_5__ {scalar_t__ bui_nextents; struct xfs_map_extent* bui_extents; } ;
struct xfs_bui_log_item {int /*<<< orphan*/  bui_flags; TYPE_1__ bui_format; } ;
struct xfs_bud_log_item {int dummy; } ;
struct xfs_bmbt_irec {int /*<<< orphan*/  br_state; int /*<<< orphan*/  br_startoff; scalar_t__ br_blockcount; int /*<<< orphan*/  br_startblock; } ;
typedef  enum xfs_bmap_intent_type { ____Placeholder_xfs_bmap_intent_type } xfs_bmap_intent_type ;
struct TYPE_8__ {int /*<<< orphan*/  tr_itruncate; } ;
struct TYPE_7__ {scalar_t__ i_nlink; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EFSCORRUPTED ; 
 int EIO ; 
 TYPE_4__* M_RES (struct xfs_mount*) ; 
 TYPE_3__* VFS_I (struct xfs_inode*) ; 
 int XFS_ATTR_FORK ; 
 scalar_t__ XFS_BB_TO_FSB (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int XFS_BMAP_EXTENT_ATTR_FORK ; 
 int XFS_BMAP_EXTENT_FLAGS ; 
 int XFS_BMAP_EXTENT_TYPE_MASK ; 
 int XFS_BMAP_EXTENT_UNWRITTEN ; 
#define  XFS_BMAP_MAP 129 
#define  XFS_BMAP_UNMAP 128 
 scalar_t__ XFS_BUI_MAX_FAST_EXTENTS ; 
 int /*<<< orphan*/  XFS_BUI_RECOVERED ; 
 int XFS_DATA_FORK ; 
 int /*<<< orphan*/  XFS_EXTENTADD_SPACE_RES (struct xfs_mount*,int) ; 
 int /*<<< orphan*/  XFS_EXT_NORM ; 
 int /*<<< orphan*/  XFS_EXT_UNWRITTEN ; 
 int /*<<< orphan*/  XFS_FSB_TO_DADDR (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_INO_TO_FSB (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_IRECOVERY ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_bmap_unmap_extent (struct xfs_trans*,struct xfs_inode*,struct xfs_bmbt_irec*) ; 
 int /*<<< orphan*/  xfs_bui_release (struct xfs_bui_log_item*) ; 
 int /*<<< orphan*/  xfs_defer_move (struct xfs_trans*,struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_iflags_set (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_iget (struct xfs_mount*,struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_inode**) ; 
 int /*<<< orphan*/  xfs_irele (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_trans_alloc (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_trans**) ; 
 int /*<<< orphan*/  xfs_trans_cancel (struct xfs_trans*) ; 
 int xfs_trans_commit (struct xfs_trans*) ; 
 struct xfs_bud_log_item* xfs_trans_get_bud (struct xfs_trans*,struct xfs_bui_log_item*) ; 
 int /*<<< orphan*/  xfs_trans_ijoin (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_trans_log_finish_bmap_update (struct xfs_trans*,struct xfs_bud_log_item*,int,struct xfs_inode*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

int
xfs_bui_recover(
	struct xfs_trans		*parent_tp,
	struct xfs_bui_log_item		*buip)
{
	int				error = 0;
	unsigned int			bui_type;
	struct xfs_map_extent		*bmap;
	xfs_fsblock_t			startblock_fsb;
	xfs_fsblock_t			inode_fsb;
	xfs_filblks_t			count;
	bool				op_ok;
	struct xfs_bud_log_item		*budp;
	enum xfs_bmap_intent_type	type;
	int				whichfork;
	xfs_exntst_t			state;
	struct xfs_trans		*tp;
	struct xfs_inode		*ip = NULL;
	struct xfs_bmbt_irec		irec;
	struct xfs_mount		*mp = parent_tp->t_mountp;

	ASSERT(!test_bit(XFS_BUI_RECOVERED, &buip->bui_flags));

	/* Only one mapping operation per BUI... */
	if (buip->bui_format.bui_nextents != XFS_BUI_MAX_FAST_EXTENTS) {
		set_bit(XFS_BUI_RECOVERED, &buip->bui_flags);
		xfs_bui_release(buip);
		return -EIO;
	}

	/*
	 * First check the validity of the extent described by the
	 * BUI.  If anything is bad, then toss the BUI.
	 */
	bmap = &buip->bui_format.bui_extents[0];
	startblock_fsb = XFS_BB_TO_FSB(mp,
			   XFS_FSB_TO_DADDR(mp, bmap->me_startblock));
	inode_fsb = XFS_BB_TO_FSB(mp, XFS_FSB_TO_DADDR(mp,
			XFS_INO_TO_FSB(mp, bmap->me_owner)));
	switch (bmap->me_flags & XFS_BMAP_EXTENT_TYPE_MASK) {
	case XFS_BMAP_MAP:
	case XFS_BMAP_UNMAP:
		op_ok = true;
		break;
	default:
		op_ok = false;
		break;
	}
	if (!op_ok || startblock_fsb == 0 ||
	    bmap->me_len == 0 ||
	    inode_fsb == 0 ||
	    startblock_fsb >= mp->m_sb.sb_dblocks ||
	    bmap->me_len >= mp->m_sb.sb_agblocks ||
	    inode_fsb >= mp->m_sb.sb_dblocks ||
	    (bmap->me_flags & ~XFS_BMAP_EXTENT_FLAGS)) {
		/*
		 * This will pull the BUI from the AIL and
		 * free the memory associated with it.
		 */
		set_bit(XFS_BUI_RECOVERED, &buip->bui_flags);
		xfs_bui_release(buip);
		return -EIO;
	}

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_itruncate,
			XFS_EXTENTADD_SPACE_RES(mp, XFS_DATA_FORK), 0, 0, &tp);
	if (error)
		return error;
	/*
	 * Recovery stashes all deferred ops during intent processing and
	 * finishes them on completion. Transfer current dfops state to this
	 * transaction and transfer the result back before we return.
	 */
	xfs_defer_move(tp, parent_tp);
	budp = xfs_trans_get_bud(tp, buip);

	/* Grab the inode. */
	error = xfs_iget(mp, tp, bmap->me_owner, 0, XFS_ILOCK_EXCL, &ip);
	if (error)
		goto err_inode;

	if (VFS_I(ip)->i_nlink == 0)
		xfs_iflags_set(ip, XFS_IRECOVERY);

	/* Process deferred bmap item. */
	state = (bmap->me_flags & XFS_BMAP_EXTENT_UNWRITTEN) ?
			XFS_EXT_UNWRITTEN : XFS_EXT_NORM;
	whichfork = (bmap->me_flags & XFS_BMAP_EXTENT_ATTR_FORK) ?
			XFS_ATTR_FORK : XFS_DATA_FORK;
	bui_type = bmap->me_flags & XFS_BMAP_EXTENT_TYPE_MASK;
	switch (bui_type) {
	case XFS_BMAP_MAP:
	case XFS_BMAP_UNMAP:
		type = bui_type;
		break;
	default:
		error = -EFSCORRUPTED;
		goto err_inode;
	}
	xfs_trans_ijoin(tp, ip, 0);

	count = bmap->me_len;
	error = xfs_trans_log_finish_bmap_update(tp, budp, type, ip, whichfork,
			bmap->me_startoff, bmap->me_startblock, &count, state);
	if (error)
		goto err_inode;

	if (count > 0) {
		ASSERT(type == XFS_BMAP_UNMAP);
		irec.br_startblock = bmap->me_startblock;
		irec.br_blockcount = count;
		irec.br_startoff = bmap->me_startoff;
		irec.br_state = state;
		xfs_bmap_unmap_extent(tp, ip, &irec);
	}

	set_bit(XFS_BUI_RECOVERED, &buip->bui_flags);
	xfs_defer_move(parent_tp, tp);
	error = xfs_trans_commit(tp);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	xfs_irele(ip);

	return error;

err_inode:
	xfs_defer_move(parent_tp, tp);
	xfs_trans_cancel(tp);
	if (ip) {
		xfs_iunlock(ip, XFS_ILOCK_EXCL);
		xfs_irele(ip);
	}
	return error;
}