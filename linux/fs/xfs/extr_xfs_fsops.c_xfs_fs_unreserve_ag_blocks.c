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
typedef  scalar_t__ xfs_agnumber_t ;
struct xfs_perag {int dummy; } ;
struct TYPE_2__ {scalar_t__ sb_agcount; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;

/* Variables and functions */
 int xfs_ag_resv_free (struct xfs_perag*) ; 
 struct xfs_perag* xfs_perag_get (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_perag_put (struct xfs_perag*) ; 
 int /*<<< orphan*/  xfs_warn (struct xfs_mount*,char*,int) ; 

int
xfs_fs_unreserve_ag_blocks(
	struct xfs_mount	*mp)
{
	xfs_agnumber_t		agno;
	struct xfs_perag	*pag;
	int			error = 0;
	int			err2;

	for (agno = 0; agno < mp->m_sb.sb_agcount; agno++) {
		pag = xfs_perag_get(mp, agno);
		err2 = xfs_ag_resv_free(pag);
		xfs_perag_put(pag);
		if (err2 && !error)
			error = err2;
	}

	if (error)
		xfs_warn(mp,
	"Error %d freeing per-AG metadata reserve pool.", error);

	return error;
}