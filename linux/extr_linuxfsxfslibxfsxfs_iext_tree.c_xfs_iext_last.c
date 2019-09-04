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
struct xfs_ifork {int dummy; } ;
struct xfs_iext_cursor {int pos; TYPE_1__* leaf; } ;
struct TYPE_2__ {int /*<<< orphan*/ * recs; } ;

/* Variables and functions */
 TYPE_1__* xfs_iext_find_last_leaf (struct xfs_ifork*) ; 
 int xfs_iext_max_recs (struct xfs_ifork*) ; 
 scalar_t__ xfs_iext_rec_is_empty (int /*<<< orphan*/ *) ; 

void
xfs_iext_last(
	struct xfs_ifork	*ifp,
	struct xfs_iext_cursor	*cur)
{
	int			i;

	cur->leaf = xfs_iext_find_last_leaf(ifp);
	if (!cur->leaf) {
		cur->pos = 0;
		return;
	}

	for (i = 1; i < xfs_iext_max_recs(ifp); i++) {
		if (xfs_iext_rec_is_empty(&cur->leaf->recs[i]))
			break;
	}
	cur->pos = i - 1;
}