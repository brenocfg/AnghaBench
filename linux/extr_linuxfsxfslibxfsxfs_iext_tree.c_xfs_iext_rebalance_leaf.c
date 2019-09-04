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
typedef  int /*<<< orphan*/  xfs_fileoff_t ;
struct xfs_ifork {int dummy; } ;
struct xfs_iext_leaf {struct xfs_iext_leaf* prev; struct xfs_iext_leaf* next; int /*<<< orphan*/ * recs; } ;
struct xfs_iext_cursor {int pos; struct xfs_iext_leaf* leaf; } ;

/* Variables and functions */
 int RECS_PER_LEAF ; 
 int /*<<< orphan*/  xfs_iext_leaf_key (struct xfs_iext_leaf*,int /*<<< orphan*/ ) ; 
 int xfs_iext_leaf_nr_entries (struct xfs_ifork*,struct xfs_iext_leaf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iext_remove_node (struct xfs_ifork*,int /*<<< orphan*/ ,struct xfs_iext_leaf*) ; 

__attribute__((used)) static void
xfs_iext_rebalance_leaf(
	struct xfs_ifork	*ifp,
	struct xfs_iext_cursor	*cur,
	struct xfs_iext_leaf	*leaf,
	xfs_fileoff_t		offset,
	int			nr_entries)
{
	/*
	 * If the neighbouring nodes are completely full we might never be able
	 * to merge our node, and will only delete it once the number of
	 * entries hits zero.
	 */
	if (nr_entries == 0)
		goto remove_node;

	if (leaf->prev) {
		int nr_prev = xfs_iext_leaf_nr_entries(ifp, leaf->prev, 0), i;

		if (nr_prev + nr_entries <= RECS_PER_LEAF) {
			for (i = 0; i < nr_entries; i++)
				leaf->prev->recs[nr_prev + i] = leaf->recs[i];

			if (cur->leaf == leaf) {
				cur->leaf = leaf->prev;
				cur->pos += nr_prev;
			}
			goto remove_node;
		}
	}

	if (leaf->next) {
		int nr_next = xfs_iext_leaf_nr_entries(ifp, leaf->next, 0), i;

		if (nr_entries + nr_next <= RECS_PER_LEAF) {
			/*
			 * Merge the next node into this node so that we don't
			 * have to do an additional update of the keys in the
			 * higher levels.
			 */
			for (i = 0; i < nr_next; i++) {
				leaf->recs[nr_entries + i] =
					leaf->next->recs[i];
			}

			if (cur->leaf == leaf->next) {
				cur->leaf = leaf;
				cur->pos += nr_entries;
			}

			offset = xfs_iext_leaf_key(leaf->next, 0);
			leaf = leaf->next;
			goto remove_node;
		}
	}

	return;
remove_node:
	if (leaf->prev)
		leaf->prev->next = leaf->next;
	if (leaf->next)
		leaf->next->prev = leaf->prev;
	xfs_iext_remove_node(ifp, offset, leaf);
}