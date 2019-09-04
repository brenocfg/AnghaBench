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
struct xfs_buf {int b_flags; } ;

/* Variables and functions */
 int XBF_ASYNC ; 
 int __xfs_buf_submit (struct xfs_buf*,int) ; 

__attribute__((used)) static inline int xfs_buf_submit(struct xfs_buf *bp)
{
	bool wait = bp->b_flags & XBF_ASYNC ? false : true;
	return __xfs_buf_submit(bp, wait);
}