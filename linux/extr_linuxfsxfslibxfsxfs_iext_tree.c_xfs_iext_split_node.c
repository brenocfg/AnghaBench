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
struct xfs_iext_node {void** keys; int /*<<< orphan*/ ** ptrs; } ;

/* Variables and functions */
 int KEYS_PER_NODE ; 
 int /*<<< orphan*/  KM_NOFS ; 
 int /*<<< orphan*/  NODE_SIZE ; 
 void* XFS_IEXT_KEY_INVALID ; 
 struct xfs_iext_node* kmem_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xfs_iext_node *
xfs_iext_split_node(
	struct xfs_iext_node	**nodep,
	int			*pos,
	int			*nr_entries)
{
	struct xfs_iext_node	*node = *nodep;
	struct xfs_iext_node	*new = kmem_zalloc(NODE_SIZE, KM_NOFS);
	const int		nr_move = KEYS_PER_NODE / 2;
	int			nr_keep = nr_move + (KEYS_PER_NODE & 1);
	int			i = 0;

	/* for sequential append operations just spill over into the new node */
	if (*pos == KEYS_PER_NODE) {
		*nodep = new;
		*pos = 0;
		*nr_entries = 0;
		goto done;
	}


	for (i = 0; i < nr_move; i++) {
		new->keys[i] = node->keys[nr_keep + i];
		new->ptrs[i] = node->ptrs[nr_keep + i];

		node->keys[nr_keep + i] = XFS_IEXT_KEY_INVALID;
		node->ptrs[nr_keep + i] = NULL;
	}

	if (*pos >= nr_keep) {
		*nodep = new;
		*pos -= nr_keep;
		*nr_entries = nr_move;
	} else {
		*nr_entries = nr_keep;
	}
done:
	for (; i < KEYS_PER_NODE; i++)
		new->keys[i] = XFS_IEXT_KEY_INVALID;
	return new;
}