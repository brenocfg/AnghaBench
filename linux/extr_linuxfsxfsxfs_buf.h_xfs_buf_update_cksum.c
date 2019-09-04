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
struct xfs_buf {int /*<<< orphan*/  b_length; int /*<<< orphan*/  b_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBTOB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_update_cksum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline void
xfs_buf_update_cksum(struct xfs_buf *bp, unsigned long cksum_offset)
{
	xfs_update_cksum(bp->b_addr, BBTOB(bp->b_length),
			 cksum_offset);
}