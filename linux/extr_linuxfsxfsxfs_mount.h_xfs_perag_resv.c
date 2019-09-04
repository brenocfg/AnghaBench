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
struct xfs_ag_resv {int dummy; } ;
struct xfs_perag {struct xfs_ag_resv pag_rmapbt_resv; struct xfs_ag_resv pag_meta_resv; } ;
typedef  enum xfs_ag_resv_type { ____Placeholder_xfs_ag_resv_type } xfs_ag_resv_type ;

/* Variables and functions */
#define  XFS_AG_RESV_METADATA 129 
#define  XFS_AG_RESV_RMAPBT 128 

__attribute__((used)) static inline struct xfs_ag_resv *
xfs_perag_resv(
	struct xfs_perag	*pag,
	enum xfs_ag_resv_type	type)
{
	switch (type) {
	case XFS_AG_RESV_METADATA:
		return &pag->pag_meta_resv;
	case XFS_AG_RESV_RMAPBT:
		return &pag->pag_rmapbt_resv;
	default:
		return NULL;
	}
}