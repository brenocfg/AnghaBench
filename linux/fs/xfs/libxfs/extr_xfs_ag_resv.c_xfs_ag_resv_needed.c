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
typedef  scalar_t__ xfs_extlen_t ;
struct TYPE_5__ {scalar_t__ ar_reserved; } ;
struct TYPE_4__ {scalar_t__ ar_reserved; } ;
struct xfs_perag {TYPE_2__ pag_rmapbt_resv; TYPE_1__ pag_meta_resv; } ;
typedef  enum xfs_ag_resv_type { ____Placeholder_xfs_ag_resv_type } xfs_ag_resv_type ;
struct TYPE_6__ {int /*<<< orphan*/  ar_reserved; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  XFS_AG_RESV_METADATA 130 
#define  XFS_AG_RESV_NONE 129 
#define  XFS_AG_RESV_RMAPBT 128 
 int /*<<< orphan*/  trace_xfs_ag_resv_needed (struct xfs_perag*,int,scalar_t__) ; 
 TYPE_3__* xfs_perag_resv (struct xfs_perag*,int) ; 

xfs_extlen_t
xfs_ag_resv_needed(
	struct xfs_perag		*pag,
	enum xfs_ag_resv_type		type)
{
	xfs_extlen_t			len;

	len = pag->pag_meta_resv.ar_reserved + pag->pag_rmapbt_resv.ar_reserved;
	switch (type) {
	case XFS_AG_RESV_METADATA:
	case XFS_AG_RESV_RMAPBT:
		len -= xfs_perag_resv(pag, type)->ar_reserved;
		break;
	case XFS_AG_RESV_NONE:
		/* empty */
		break;
	default:
		ASSERT(0);
	}

	trace_xfs_ag_resv_needed(pag, type, len);

	return len;
}