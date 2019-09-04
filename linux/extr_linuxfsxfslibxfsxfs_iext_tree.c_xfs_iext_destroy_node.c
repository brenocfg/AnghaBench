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
struct xfs_iext_node {scalar_t__* keys; struct xfs_iext_node** ptrs; } ;

/* Variables and functions */
 int KEYS_PER_NODE ; 
 scalar_t__ XFS_IEXT_KEY_INVALID ; 
 int /*<<< orphan*/  kmem_free (struct xfs_iext_node*) ; 

__attribute__((used)) static void
xfs_iext_destroy_node(
	struct xfs_iext_node	*node,
	int			level)
{
	int			i;

	if (level > 1) {
		for (i = 0; i < KEYS_PER_NODE; i++) {
			if (node->keys[i] == XFS_IEXT_KEY_INVALID)
				break;
			xfs_iext_destroy_node(node->ptrs[i], level - 1);
		}
	}

	kmem_free(node);
}