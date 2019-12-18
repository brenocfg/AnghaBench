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
struct xfs_mount {struct xfs_buftarg* m_ddev_targp; } ;
struct xfs_buftarg {TYPE_1__* bt_bdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bd_queue; } ;

/* Variables and functions */
 scalar_t__ blk_queue_nonrot (int /*<<< orphan*/ ) ; 

unsigned int
xfs_pwork_guess_datadev_parallelism(
	struct xfs_mount	*mp)
{
	struct xfs_buftarg	*btp = mp->m_ddev_targp;

	/*
	 * For now we'll go with the most conservative setting possible,
	 * which is two threads for an SSD and 1 thread everywhere else.
	 */
	return blk_queue_nonrot(btp->bt_bdev->bd_queue) ? 2 : 1;
}