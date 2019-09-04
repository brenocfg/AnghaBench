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
typedef  int /*<<< orphan*/  xfs_dqid_t ;
typedef  int /*<<< orphan*/  uint ;
struct xfs_mount {int dummy; } ;
struct xfs_dquot {int dummy; } ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  trace_xfs_dqread (struct xfs_dquot*) ; 
 int /*<<< orphan*/  trace_xfs_dqread_fail (struct xfs_dquot*) ; 
 int /*<<< orphan*/  xfs_buf_islocked (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_relse (struct xfs_buf*) ; 
 struct xfs_dquot* xfs_dquot_alloc (struct xfs_mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_dquot_disk_read (struct xfs_mount*,struct xfs_dquot*,struct xfs_buf**) ; 
 int /*<<< orphan*/  xfs_dquot_from_disk (struct xfs_dquot*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_qm_dqdestroy (struct xfs_dquot*) ; 
 int xfs_qm_dqread_alloc (struct xfs_mount*,struct xfs_dquot*,struct xfs_buf**) ; 

__attribute__((used)) static int
xfs_qm_dqread(
	struct xfs_mount	*mp,
	xfs_dqid_t		id,
	uint			type,
	bool			can_alloc,
	struct xfs_dquot	**dqpp)
{
	struct xfs_dquot	*dqp;
	struct xfs_buf		*bp;
	int			error;

	dqp = xfs_dquot_alloc(mp, id, type);
	trace_xfs_dqread(dqp);

	/* Try to read the buffer, allocating if necessary. */
	error = xfs_dquot_disk_read(mp, dqp, &bp);
	if (error == -ENOENT && can_alloc)
		error = xfs_qm_dqread_alloc(mp, dqp, &bp);
	if (error)
		goto err;

	/*
	 * At this point we should have a clean locked buffer.  Copy the data
	 * to the incore dquot and release the buffer since the incore dquot
	 * has its own locking protocol so we needn't tie up the buffer any
	 * further.
	 */
	ASSERT(xfs_buf_islocked(bp));
	xfs_dquot_from_disk(dqp, bp);

	xfs_buf_relse(bp);
	*dqpp = dqp;
	return error;

err:
	trace_xfs_dqread_fail(dqp);
	xfs_qm_dqdestroy(dqp);
	*dqpp = NULL;
	return error;
}