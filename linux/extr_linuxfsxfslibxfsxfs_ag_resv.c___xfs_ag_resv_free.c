#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_extlen_t ;
struct xfs_perag {scalar_t__ pag_agno; TYPE_1__* pag_mount; } ;
struct xfs_ag_resv {scalar_t__ ar_orig_reserved; scalar_t__ ar_asked; scalar_t__ ar_reserved; } ;
typedef  enum xfs_ag_resv_type { ____Placeholder_xfs_ag_resv_type } xfs_ag_resv_type ;
struct TYPE_3__ {int /*<<< orphan*/  m_ag_max_usable; } ;

/* Variables and functions */
 int XFS_AG_RESV_RMAPBT ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  trace_xfs_ag_resv_free (struct xfs_perag*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_ag_resv_free_error (TYPE_1__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int xfs_mod_fdblocks (TYPE_1__*,scalar_t__,int) ; 
 struct xfs_ag_resv* xfs_perag_resv (struct xfs_perag*,int) ; 

__attribute__((used)) static int
__xfs_ag_resv_free(
	struct xfs_perag		*pag,
	enum xfs_ag_resv_type		type)
{
	struct xfs_ag_resv		*resv;
	xfs_extlen_t			oldresv;
	int				error;

	trace_xfs_ag_resv_free(pag, type, 0);

	resv = xfs_perag_resv(pag, type);
	if (pag->pag_agno == 0)
		pag->pag_mount->m_ag_max_usable += resv->ar_asked;
	/*
	 * RMAPBT blocks come from the AGFL and AGFL blocks are always
	 * considered "free", so whatever was reserved at mount time must be
	 * given back at umount.
	 */
	if (type == XFS_AG_RESV_RMAPBT)
		oldresv = resv->ar_orig_reserved;
	else
		oldresv = resv->ar_reserved;
	error = xfs_mod_fdblocks(pag->pag_mount, oldresv, true);
	resv->ar_reserved = 0;
	resv->ar_asked = 0;
	resv->ar_orig_reserved = 0;

	if (error)
		trace_xfs_ag_resv_free_error(pag->pag_mount, pag->pag_agno,
				error, _RET_IP_);
	return error;
}