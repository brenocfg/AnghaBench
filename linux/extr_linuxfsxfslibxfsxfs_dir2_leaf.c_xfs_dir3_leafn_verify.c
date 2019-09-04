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
typedef  int /*<<< orphan*/  xfs_failaddr_t ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DIR2_LEAFN_MAGIC ; 
 int /*<<< orphan*/  xfs_dir3_leaf_verify (struct xfs_buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static xfs_failaddr_t
xfs_dir3_leafn_verify(
	struct xfs_buf	*bp)
{
	return xfs_dir3_leaf_verify(bp, XFS_DIR2_LEAFN_MAGIC);
}