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
typedef  int xfs_daddr_t ;
struct xlog {scalar_t__ l_sectBBsize; } ;

/* Variables and functions */
 unsigned int BBTOB (int) ; 

__attribute__((used)) static inline unsigned int
xlog_align(
	struct xlog	*log,
	xfs_daddr_t	blk_no)
{
	return BBTOB(blk_no & ((xfs_daddr_t)log->l_sectBBsize - 1));
}