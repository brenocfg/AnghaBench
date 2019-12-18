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
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
typedef  int /*<<< orphan*/  xfs_filblks_t ;
struct xfs_trans {int dummy; } ;
struct xfs_owner_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xfs_bmap_add_free (struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_owner_info const*,int) ; 

__attribute__((used)) static inline void
xfs_bmap_add_free(
	struct xfs_trans		*tp,
	xfs_fsblock_t			bno,
	xfs_filblks_t			len,
	const struct xfs_owner_info	*oinfo)
{
	__xfs_bmap_add_free(tp, bno, len, oinfo, false);
}