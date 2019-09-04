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
struct xrep_findroot {struct xfs_buf* agfl_bp; int /*<<< orphan*/  agf; struct xrep_find_ag_btree* btree_info; struct xfs_scrub* sc; } ;
struct xrep_find_ag_btree {scalar_t__ rmap_owner; scalar_t__ height; int /*<<< orphan*/  root; scalar_t__ buf_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  agno; } ;
struct xfs_scrub {TYPE_1__ sa; int /*<<< orphan*/  tp; struct xfs_mount* mp; } ;
struct xfs_mount {int dummy; } ;
struct xfs_buf {int dummy; } ;
struct xfs_btree_cur {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  NULLAGBLOCK ; 
 int /*<<< orphan*/  XFS_BUF_TO_AGF (struct xfs_buf*) ; 
 int XFS_RMAP_NON_INODE_OWNER (scalar_t__) ; 
 scalar_t__ XFS_RMAP_OWN_AG ; 
 int /*<<< orphan*/  xfs_btree_del_cursor (struct xfs_btree_cur*,int) ; 
 int xfs_buf_islocked (struct xfs_buf*) ; 
 int xfs_rmap_query_all (struct xfs_btree_cur*,int /*<<< orphan*/ ,struct xrep_findroot*) ; 
 struct xfs_btree_cur* xfs_rmapbt_init_cursor (struct xfs_mount*,int /*<<< orphan*/ ,struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xrep_findroot_rmap ; 

int
xrep_find_ag_btree_roots(
	struct xfs_scrub		*sc,
	struct xfs_buf			*agf_bp,
	struct xrep_find_ag_btree	*btree_info,
	struct xfs_buf			*agfl_bp)
{
	struct xfs_mount		*mp = sc->mp;
	struct xrep_findroot		ri;
	struct xrep_find_ag_btree	*fab;
	struct xfs_btree_cur		*cur;
	int				error;

	ASSERT(xfs_buf_islocked(agf_bp));
	ASSERT(agfl_bp == NULL || xfs_buf_islocked(agfl_bp));

	ri.sc = sc;
	ri.btree_info = btree_info;
	ri.agf = XFS_BUF_TO_AGF(agf_bp);
	ri.agfl_bp = agfl_bp;
	for (fab = btree_info; fab->buf_ops; fab++) {
		ASSERT(agfl_bp || fab->rmap_owner != XFS_RMAP_OWN_AG);
		ASSERT(XFS_RMAP_NON_INODE_OWNER(fab->rmap_owner));
		fab->root = NULLAGBLOCK;
		fab->height = 0;
	}

	cur = xfs_rmapbt_init_cursor(mp, sc->tp, agf_bp, sc->sa.agno);
	error = xfs_rmap_query_all(cur, xrep_findroot_rmap, &ri);
	xfs_btree_del_cursor(cur, error);

	return error;
}