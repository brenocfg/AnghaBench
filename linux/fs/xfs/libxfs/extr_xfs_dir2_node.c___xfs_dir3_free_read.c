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
typedef  scalar_t__ xfs_failaddr_t ;
typedef  int /*<<< orphan*/  xfs_daddr_t ;
typedef  int /*<<< orphan*/  xfs_dablk_t ;
struct xfs_trans {int dummy; } ;
struct xfs_inode {int dummy; } ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  XFS_BLFT_DIR_FREE_BUF ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int xfs_da_read_buf (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_buf**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_dir3_free_buf_ops ; 
 scalar_t__ xfs_dir3_free_header_check (struct xfs_inode*,int /*<<< orphan*/ ,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_trans_brelse (struct xfs_trans*,struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_trans_buf_set_type (struct xfs_trans*,struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_verifier_error (struct xfs_buf*,int,scalar_t__) ; 

__attribute__((used)) static int
__xfs_dir3_free_read(
	struct xfs_trans	*tp,
	struct xfs_inode	*dp,
	xfs_dablk_t		fbno,
	xfs_daddr_t		mappedbno,
	struct xfs_buf		**bpp)
{
	xfs_failaddr_t		fa;
	int			err;

	err = xfs_da_read_buf(tp, dp, fbno, mappedbno, bpp,
				XFS_DATA_FORK, &xfs_dir3_free_buf_ops);
	if (err || !*bpp)
		return err;

	/* Check things that we can't do in the verifier. */
	fa = xfs_dir3_free_header_check(dp, fbno, *bpp);
	if (fa) {
		xfs_verifier_error(*bpp, -EFSCORRUPTED, fa);
		xfs_trans_brelse(tp, *bpp);
		return -EFSCORRUPTED;
	}

	/* try read returns without an error or *bpp if it lands in a hole */
	if (tp)
		xfs_trans_buf_set_type(tp, *bpp, XFS_BLFT_DIR_FREE_BUF);

	return 0;
}