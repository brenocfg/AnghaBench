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
struct nilfs_btree_node {int dummy; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * nilfs_btree_node_dkeys (struct nilfs_btree_node*) ; 
 int /*<<< orphan*/ * nilfs_btree_node_dptrs (struct nilfs_btree_node*,int) ; 
 int nilfs_btree_node_get_nchildren (struct nilfs_btree_node*) ; 
 int /*<<< orphan*/  nilfs_btree_node_set_nchildren (struct nilfs_btree_node*,int) ; 

__attribute__((used)) static void nilfs_btree_node_move_left(struct nilfs_btree_node *left,
				       struct nilfs_btree_node *right,
				       int n, int lncmax, int rncmax)
{
	__le64 *ldkeys, *rdkeys;
	__le64 *ldptrs, *rdptrs;
	int lnchildren, rnchildren;

	ldkeys = nilfs_btree_node_dkeys(left);
	ldptrs = nilfs_btree_node_dptrs(left, lncmax);
	lnchildren = nilfs_btree_node_get_nchildren(left);

	rdkeys = nilfs_btree_node_dkeys(right);
	rdptrs = nilfs_btree_node_dptrs(right, rncmax);
	rnchildren = nilfs_btree_node_get_nchildren(right);

	memcpy(ldkeys + lnchildren, rdkeys, n * sizeof(*rdkeys));
	memcpy(ldptrs + lnchildren, rdptrs, n * sizeof(*rdptrs));
	memmove(rdkeys, rdkeys + n, (rnchildren - n) * sizeof(*rdkeys));
	memmove(rdptrs, rdptrs + n, (rnchildren - n) * sizeof(*rdptrs));

	lnchildren += n;
	rnchildren -= n;
	nilfs_btree_node_set_nchildren(left, lnchildren);
	nilfs_btree_node_set_nchildren(right, rnchildren);
}