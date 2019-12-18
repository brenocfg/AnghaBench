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
struct xfs_inumbers_chunk {struct xfs_ibulk* breq; int /*<<< orphan*/  formatter; } ;
struct xfs_ibulk {scalar_t__ ocount; int /*<<< orphan*/  icount; int /*<<< orphan*/  flags; int /*<<< orphan*/  startino; int /*<<< orphan*/  mp; } ;
typedef  int /*<<< orphan*/  inumbers_fmt_pf ;

/* Variables and functions */
 scalar_t__ xfs_bulkstat_already_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_inobt_walk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_inumbers_chunk*) ; 
 int /*<<< orphan*/  xfs_inumbers_walk ; 

int
xfs_inumbers(
	struct xfs_ibulk	*breq,
	inumbers_fmt_pf		formatter)
{
	struct xfs_inumbers_chunk ic = {
		.formatter	= formatter,
		.breq		= breq,
	};
	int			error = 0;

	if (xfs_bulkstat_already_done(breq->mp, breq->startino))
		return 0;

	error = xfs_inobt_walk(breq->mp, NULL, breq->startino, breq->flags,
			xfs_inumbers_walk, breq->icount, &ic);

	/*
	 * We found some inode groups, so clear the error status and return
	 * them.  The lastino pointer will point directly at the inode that
	 * triggered any error that occurred, so on the next call the error
	 * will be triggered again and propagated to userspace as there will be
	 * no formatted inode groups in the buffer.
	 */
	if (breq->ocount > 0)
		error = 0;

	return error;
}