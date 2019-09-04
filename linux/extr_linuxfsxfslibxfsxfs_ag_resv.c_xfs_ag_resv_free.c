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
struct xfs_perag {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_AG_RESV_METADATA ; 
 int /*<<< orphan*/  XFS_AG_RESV_RMAPBT ; 
 int __xfs_ag_resv_free (struct xfs_perag*,int /*<<< orphan*/ ) ; 

int
xfs_ag_resv_free(
	struct xfs_perag		*pag)
{
	int				error;
	int				err2;

	error = __xfs_ag_resv_free(pag, XFS_AG_RESV_RMAPBT);
	err2 = __xfs_ag_resv_free(pag, XFS_AG_RESV_METADATA);
	if (err2 && !error)
		error = err2;
	return error;
}