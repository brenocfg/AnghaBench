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
typedef  int /*<<< orphan*/  xfs_btree_query_range_fn ;
typedef  union xfs_btree_key {int dummy; } xfs_btree_key ;
struct xfs_btree_cur {union xfs_btree_key bc_rec; } ;
typedef  int /*<<< orphan*/  low_key ;
typedef  int /*<<< orphan*/  high_key ;

/* Variables and functions */
 int /*<<< orphan*/  memset (union xfs_btree_key*,int,int) ; 
 int xfs_btree_simple_query_range (struct xfs_btree_cur*,union xfs_btree_key*,union xfs_btree_key*,int /*<<< orphan*/ ,void*) ; 

int
xfs_btree_query_all(
	struct xfs_btree_cur		*cur,
	xfs_btree_query_range_fn	fn,
	void				*priv)
{
	union xfs_btree_key		low_key;
	union xfs_btree_key		high_key;

	memset(&cur->bc_rec, 0, sizeof(cur->bc_rec));
	memset(&low_key, 0, sizeof(low_key));
	memset(&high_key, 0xFF, sizeof(high_key));

	return xfs_btree_simple_query_range(cur, &low_key, &high_key, fn, priv);
}