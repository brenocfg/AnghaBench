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
struct xfs_buftarg {TYPE_1__* bt_bdev; } ;
struct xfs_buf_ops {int dummy; } ;
struct xfs_buf_map {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bd_bdi; } ;

/* Variables and functions */
 int XBF_ASYNC ; 
 int XBF_READ_AHEAD ; 
 int XBF_TRYLOCK ; 
 scalar_t__ bdi_read_congested (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_read_map (struct xfs_buftarg*,struct xfs_buf_map*,int,int,struct xfs_buf_ops const*) ; 

void
xfs_buf_readahead_map(
	struct xfs_buftarg	*target,
	struct xfs_buf_map	*map,
	int			nmaps,
	const struct xfs_buf_ops *ops)
{
	if (bdi_read_congested(target->bt_bdev->bd_bdi))
		return;

	xfs_buf_read_map(target, map, nmaps,
		     XBF_TRYLOCK|XBF_ASYNC|XBF_READ_AHEAD, ops);
}