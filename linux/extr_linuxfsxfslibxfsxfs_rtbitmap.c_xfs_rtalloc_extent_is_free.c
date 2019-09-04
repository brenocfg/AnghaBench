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
typedef  int /*<<< orphan*/  xfs_rtblock_t ;
typedef  int /*<<< orphan*/  xfs_extlen_t ;
struct xfs_trans {int dummy; } ;
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 int xfs_rtcheck_range (struct xfs_mount*,struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 

int
xfs_rtalloc_extent_is_free(
	struct xfs_mount		*mp,
	struct xfs_trans		*tp,
	xfs_rtblock_t			start,
	xfs_extlen_t			len,
	bool				*is_free)
{
	xfs_rtblock_t			end;
	int				matches;
	int				error;

	error = xfs_rtcheck_range(mp, tp, start, len, 1, &end, &matches);
	if (error)
		return error;

	*is_free = matches;
	return 0;
}