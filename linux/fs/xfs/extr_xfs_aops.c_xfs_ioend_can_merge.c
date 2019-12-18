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
struct xfs_ioend {scalar_t__ io_fork; scalar_t__ io_state; scalar_t__ io_offset; scalar_t__ io_size; TYPE_1__* io_bio; } ;
struct TYPE_2__ {scalar_t__ bi_status; } ;

/* Variables and functions */
 scalar_t__ XFS_COW_FORK ; 
 scalar_t__ XFS_EXT_UNWRITTEN ; 

__attribute__((used)) static bool
xfs_ioend_can_merge(
	struct xfs_ioend	*ioend,
	struct xfs_ioend	*next)
{
	if (ioend->io_bio->bi_status != next->io_bio->bi_status)
		return false;
	if ((ioend->io_fork == XFS_COW_FORK) ^ (next->io_fork == XFS_COW_FORK))
		return false;
	if ((ioend->io_state == XFS_EXT_UNWRITTEN) ^
	    (next->io_state == XFS_EXT_UNWRITTEN))
		return false;
	if (ioend->io_offset + ioend->io_size != next->io_offset)
		return false;
	return true;
}