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
struct TYPE_2__ {struct xfs_iext_node* if_root; } ;
struct xfs_ifork {int if_height; TYPE_1__ if_u1; } ;
struct xfs_iext_node {int /*<<< orphan*/ * keys; struct xfs_iext_node** ptrs; } ;
struct xfs_iext_leaf {int /*<<< orphan*/ * keys; struct xfs_iext_leaf** ptrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int KEYS_PER_NODE ; 
 int /*<<< orphan*/  KM_NOFS ; 
 int /*<<< orphan*/  NODE_SIZE ; 
 int /*<<< orphan*/  XFS_IEXT_KEY_INVALID ; 
 struct xfs_iext_node* kmem_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iext_leaf_key (struct xfs_iext_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_iext_grow(
	struct xfs_ifork	*ifp)
{
	struct xfs_iext_node	*node = kmem_zalloc(NODE_SIZE, KM_NOFS);
	int			i;

	if (ifp->if_height == 1) {
		struct xfs_iext_leaf *prev = ifp->if_u1.if_root;

		node->keys[0] = xfs_iext_leaf_key(prev, 0);
		node->ptrs[0] = prev;
	} else  {
		struct xfs_iext_node *prev = ifp->if_u1.if_root;

		ASSERT(ifp->if_height > 1);

		node->keys[0] = prev->keys[0];
		node->ptrs[0] = prev;
	}

	for (i = 1; i < KEYS_PER_NODE; i++)
		node->keys[i] = XFS_IEXT_KEY_INVALID;

	ifp->if_u1.if_root = node;
	ifp->if_height++;
}