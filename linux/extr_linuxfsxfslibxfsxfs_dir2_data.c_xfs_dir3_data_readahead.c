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
typedef  int /*<<< orphan*/  xfs_daddr_t ;
typedef  int /*<<< orphan*/  xfs_dablk_t ;
struct xfs_inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int xfs_da_reada_buf (struct xfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_dir3_data_reada_buf_ops ; 

int
xfs_dir3_data_readahead(
	struct xfs_inode	*dp,
	xfs_dablk_t		bno,
	xfs_daddr_t		mapped_bno)
{
	return xfs_da_reada_buf(dp, bno, mapped_bno,
				XFS_DATA_FORK, &xfs_dir3_data_reada_buf_ops);
}