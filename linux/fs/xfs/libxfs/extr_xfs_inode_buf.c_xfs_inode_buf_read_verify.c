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
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfs_inode_buf_verify (struct xfs_buf*,int) ; 

__attribute__((used)) static void
xfs_inode_buf_read_verify(
	struct xfs_buf	*bp)
{
	xfs_inode_buf_verify(bp, false);
}