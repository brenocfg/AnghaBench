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
struct xfs_ibulk {int /*<<< orphan*/  ubuffer; int /*<<< orphan*/  mp; } ;
struct xfs_bulkstat {int dummy; } ;
struct xfs_bstat {int dummy; } ;
typedef  int /*<<< orphan*/  bs1 ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct xfs_bstat*,int) ; 
 int /*<<< orphan*/  xfs_bulkstat_to_bstat (int /*<<< orphan*/ ,struct xfs_bstat*,struct xfs_bulkstat const*) ; 
 int xfs_ibulk_advance (struct xfs_ibulk*,int) ; 

int
xfs_fsbulkstat_one_fmt(
	struct xfs_ibulk		*breq,
	const struct xfs_bulkstat	*bstat)
{
	struct xfs_bstat		bs1;

	xfs_bulkstat_to_bstat(breq->mp, &bs1, bstat);
	if (copy_to_user(breq->ubuffer, &bs1, sizeof(bs1)))
		return -EFAULT;
	return xfs_ibulk_advance(breq, sizeof(struct xfs_bstat));
}