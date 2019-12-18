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
typedef  union xfs_btree_irec {int dummy; } xfs_btree_irec ;
struct xfs_btree_cur {int dummy; } ;

/* Variables and functions */
 int ECANCELED ; 
 int /*<<< orphan*/  xfs_btree_has_record_helper ; 
 int xfs_btree_query_range (struct xfs_btree_cur*,union xfs_btree_irec*,union xfs_btree_irec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
xfs_btree_has_record(
	struct xfs_btree_cur	*cur,
	union xfs_btree_irec	*low,
	union xfs_btree_irec	*high,
	bool			*exists)
{
	int			error;

	error = xfs_btree_query_range(cur, low, high,
			&xfs_btree_has_record_helper, NULL);
	if (error == -ECANCELED) {
		*exists = true;
		return 0;
	}
	*exists = false;
	return error;
}