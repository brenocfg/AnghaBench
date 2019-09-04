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
typedef  int /*<<< orphan*/  uint ;
struct xfs_trans {int dummy; } ;
struct xfs_buftarg {int dummy; } ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_SINGLE_BUF_MAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  map ; 
 struct xfs_buf* xfs_trans_get_buf_map (struct xfs_trans*,struct xfs_buftarg*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct xfs_buf *
xfs_trans_get_buf(
	struct xfs_trans	*tp,
	struct xfs_buftarg	*target,
	xfs_daddr_t		blkno,
	int			numblks,
	uint			flags)
{
	DEFINE_SINGLE_BUF_MAP(map, blkno, numblks);
	return xfs_trans_get_buf_map(tp, target, &map, 1, flags);
}