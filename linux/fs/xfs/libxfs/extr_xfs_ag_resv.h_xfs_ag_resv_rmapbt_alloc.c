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
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
struct xfs_perag {int dummy; } ;
struct xfs_mount {int dummy; } ;
struct xfs_alloc_arg {int len; int /*<<< orphan*/ * member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_AG_RESV_RMAPBT ; 
 int /*<<< orphan*/  xfs_ag_resv_alloc_extent (struct xfs_perag*,int /*<<< orphan*/ ,struct xfs_alloc_arg*) ; 
 struct xfs_perag* xfs_perag_get (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_perag_put (struct xfs_perag*) ; 

__attribute__((used)) static inline void
xfs_ag_resv_rmapbt_alloc(
	struct xfs_mount	*mp,
	xfs_agnumber_t		agno)
{
	struct xfs_alloc_arg	args = { NULL };
	struct xfs_perag	*pag;

	args.len = 1;
	pag = xfs_perag_get(mp, agno);
	xfs_ag_resv_alloc_extent(pag, XFS_AG_RESV_RMAPBT, &args);
	xfs_perag_put(pag);
}