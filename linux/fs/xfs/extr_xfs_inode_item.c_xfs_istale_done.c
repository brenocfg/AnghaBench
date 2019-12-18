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
struct xfs_log_item {int dummy; } ;
struct xfs_buf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ili_inode; } ;

/* Variables and functions */
 TYPE_1__* INODE_ITEM (struct xfs_log_item*) ; 
 int /*<<< orphan*/  xfs_iflush_abort (int /*<<< orphan*/ ,int) ; 

void
xfs_istale_done(
	struct xfs_buf		*bp,
	struct xfs_log_item	*lip)
{
	xfs_iflush_abort(INODE_ITEM(lip)->ili_inode, true);
}