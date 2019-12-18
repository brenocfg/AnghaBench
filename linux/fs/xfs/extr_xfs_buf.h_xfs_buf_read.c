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
typedef  int /*<<< orphan*/  xfs_buf_flags_t ;
struct xfs_buftarg {int dummy; } ;
struct xfs_buf_ops {int dummy; } ;
struct xfs_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_SINGLE_BUF_MAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  map ; 
 struct xfs_buf* xfs_buf_read_map (struct xfs_buftarg*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct xfs_buf_ops const*) ; 

__attribute__((used)) static inline struct xfs_buf *
xfs_buf_read(
	struct xfs_buftarg	*target,
	xfs_daddr_t		blkno,
	size_t			numblks,
	xfs_buf_flags_t		flags,
	const struct xfs_buf_ops *ops)
{
	DEFINE_SINGLE_BUF_MAP(map, blkno, numblks);
	return xfs_buf_read_map(target, &map, 1, flags, ops);
}