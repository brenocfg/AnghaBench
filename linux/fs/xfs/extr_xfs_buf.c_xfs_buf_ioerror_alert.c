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
typedef  int /*<<< orphan*/  uint64_t ;
struct xfs_buf {int /*<<< orphan*/  b_error; int /*<<< orphan*/  b_length; int /*<<< orphan*/  b_mount; } ;

/* Variables and functions */
 scalar_t__ XFS_BUF_ADDR (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_alert (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xfs_buf_ioerror_alert(
	struct xfs_buf		*bp,
	const char		*func)
{
	xfs_alert(bp->b_mount,
"metadata I/O error in \"%s\" at daddr 0x%llx len %d error %d",
			func, (uint64_t)XFS_BUF_ADDR(bp), bp->b_length,
			-bp->b_error);
}