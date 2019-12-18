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
typedef  scalar_t__ xfs_filblks_t ;
struct xfs_scrub {int dummy; } ;
struct xfs_owner_info {int dummy; } ;
struct xfs_btree_cur {int dummy; } ;
struct xchk_rmap_ownedby_info {scalar_t__* blocks; struct xfs_owner_info const* oinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  xchk_count_rmap_ownedby_irec ; 
 int xfs_rmap_query_all (struct xfs_btree_cur*,int /*<<< orphan*/ ,struct xchk_rmap_ownedby_info*) ; 

int
xchk_count_rmap_ownedby_ag(
	struct xfs_scrub		*sc,
	struct xfs_btree_cur		*cur,
	const struct xfs_owner_info	*oinfo,
	xfs_filblks_t			*blocks)
{
	struct xchk_rmap_ownedby_info	sroi = {
		.oinfo			= oinfo,
		.blocks			= blocks,
	};

	*blocks = 0;
	return xfs_rmap_query_all(cur, xchk_count_rmap_ownedby_irec,
			&sroi);
}