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
typedef  int /*<<< orphan*/  uint64_t ;
struct xfs_ifork {int if_height; } ;
struct xfs_iext_node {int /*<<< orphan*/ * keys; void** ptrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int KEYS_PER_NODE ; 
 struct xfs_iext_node* xfs_iext_find_level (struct xfs_ifork*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_iext_grow (struct xfs_ifork*) ; 
 scalar_t__ xfs_iext_key_cmp (struct xfs_iext_node*,int,int /*<<< orphan*/ ) ; 
 int xfs_iext_node_insert_pos (struct xfs_iext_node*,int /*<<< orphan*/ ) ; 
 int xfs_iext_node_nr_entries (struct xfs_iext_node*,int) ; 
 struct xfs_iext_node* xfs_iext_split_node (struct xfs_iext_node**,int*,int*) ; 
 int /*<<< orphan*/  xfs_iext_update_node (struct xfs_ifork*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct xfs_iext_node*) ; 

__attribute__((used)) static void
xfs_iext_insert_node(
	struct xfs_ifork	*ifp,
	uint64_t		offset,
	void			*ptr,
	int			level)
{
	struct xfs_iext_node	*node, *new;
	int			i, pos, nr_entries;

again:
	if (ifp->if_height < level)
		xfs_iext_grow(ifp);

	new = NULL;
	node = xfs_iext_find_level(ifp, offset, level);
	pos = xfs_iext_node_insert_pos(node, offset);
	nr_entries = xfs_iext_node_nr_entries(node, pos);

	ASSERT(pos >= nr_entries || xfs_iext_key_cmp(node, pos, offset) != 0);
	ASSERT(nr_entries <= KEYS_PER_NODE);

	if (nr_entries == KEYS_PER_NODE)
		new = xfs_iext_split_node(&node, &pos, &nr_entries);

	/*
	 * Update the pointers in higher levels if the first entry changes
	 * in an existing node.
	 */
	if (node != new && pos == 0 && nr_entries > 0)
		xfs_iext_update_node(ifp, node->keys[0], offset, level, node);

	for (i = nr_entries; i > pos; i--) {
		node->keys[i] = node->keys[i - 1];
		node->ptrs[i] = node->ptrs[i - 1];
	}
	node->keys[pos] = offset;
	node->ptrs[pos] = ptr;

	if (new) {
		offset = new->keys[0];
		ptr = new;
		level++;
		goto again;
	}
}