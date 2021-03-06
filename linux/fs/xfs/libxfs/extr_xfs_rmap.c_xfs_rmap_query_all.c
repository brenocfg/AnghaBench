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
typedef  int /*<<< orphan*/  xfs_rmap_query_range_fn ;
struct xfs_rmap_query_range_info {int /*<<< orphan*/  fn; void* priv; } ;
struct xfs_btree_cur {int dummy; } ;

/* Variables and functions */
 int xfs_btree_query_all (struct xfs_btree_cur*,int /*<<< orphan*/ ,struct xfs_rmap_query_range_info*) ; 
 int /*<<< orphan*/  xfs_rmap_query_range_helper ; 

int
xfs_rmap_query_all(
	struct xfs_btree_cur			*cur,
	xfs_rmap_query_range_fn			fn,
	void					*priv)
{
	struct xfs_rmap_query_range_info	query;

	query.priv = priv;
	query.fn = fn;
	return xfs_btree_query_all(cur, xfs_rmap_query_range_helper, &query);
}