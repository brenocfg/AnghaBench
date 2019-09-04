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

__attribute__((used)) static inline bool
xlog_verify_bp(
	struct xlog	*log,
	xfs_daddr_t	blk_no,
	int		bbcount)
{
	if (blk_no < 0 || blk_no >= log->l_logBBsize)
		return false;
	if (bbcount <= 0 || (blk_no + bbcount) > log->l_logBBsize)
		return false;
	return true;
}