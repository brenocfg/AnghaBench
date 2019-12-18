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
typedef  void* xfs_daddr_t ;
struct xfs_mount {int /*<<< orphan*/  m_ddev_targp; } ;
struct xfs_buf_ops {int dummy; } ;
struct xfs_buf {struct xfs_buf_ops const* b_ops; TYPE_1__* b_maps; void* b_bn; int /*<<< orphan*/  b_length; } ;
struct TYPE_2__ {void* bm_bn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBTOB (int /*<<< orphan*/ ) ; 
 struct xfs_buf* xfs_buf_get_uncached (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_zero (struct xfs_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xfs_buf *
xfs_get_aghdr_buf(
	struct xfs_mount	*mp,
	xfs_daddr_t		blkno,
	size_t			numblks,
	const struct xfs_buf_ops *ops)
{
	struct xfs_buf		*bp;

	bp = xfs_buf_get_uncached(mp->m_ddev_targp, numblks, 0);
	if (!bp)
		return NULL;

	xfs_buf_zero(bp, 0, BBTOB(bp->b_length));
	bp->b_bn = blkno;
	bp->b_maps[0].bm_bn = blkno;
	bp->b_ops = ops;

	return bp;
}