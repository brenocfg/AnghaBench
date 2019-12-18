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
typedef  scalar_t__ xfs_daddr_t ;
struct xlog {scalar_t__ l_logBBsize; } ;

/* Variables and functions */

__attribute__((used)) static inline int
xlog_tail_distance(
	struct xlog	*log,
	xfs_daddr_t	head_blk,
	xfs_daddr_t	tail_blk)
{
	if (head_blk < tail_blk)
		return tail_blk - head_blk;

	return tail_blk + (log->l_logBBsize - head_blk);
}